/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tracer_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:42:10 by eraad             #+#    #+#             */
/*   Updated: 2026/01/27 16:36:48 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_color	get_attenuation(t_material *mat, t_hit_record *rec, t_vec3 v,
		t_path_info *info)
{
	t_color	f_r;
	t_real	cos_theta;

	info->front_face = rec->front_face;
	sample_bsdf(mat, rec->normal, v, info);
	if (info->pdf < EPSILON)
		return ((t_color){0.0, 0.0, 0.0});
	if (mat->type == DIELECTRIC || mat->roughness <= 0.001)
	{
		if (mat->type == METAL || mat->metallic > 0.9)
			f_r = mat->specular_color;
		else if (color_mean(mat->specular_color) > EPSILON)
			f_r = mat->specular_color;
		else
			f_r = (t_color){1.0, 1.0, 1.0};
		if (mat->type == DIELECTRIC && mat->roughness > 0.01)
			return (color_scale(f_r, info->bsdf_weight));
		return (f_r);
	}
	f_r = eval_bsdf(mat, rec, v, info->next_dir);
	cos_theta = fmax(vec3_dot(rec->normal, info->next_dir), 0.0);
	return (color_scale(f_r, cos_theta / info->pdf));
}

static void	apply_surface_logic(t_scene *scene, t_hit_record *rec, t_vec3 v,
		t_path_info *info)
{
	t_material	*mat;
	t_color		direct_light;

	mat = rec->object->material;
	if (!rec->front_face && (mat->type == DIELECTRIC || mat->ior > 1.0))
		info->thru = beer_lambert(info->thru, rec->t, mat->absorbance);
	if (mat->roughness > 0.001
		&& (mat->type != DIELECTRIC || mat->roughness > 0.01))
	{
		if (scene->render_mode == RENDER_LIGHTS)
			direct_light = (t_color){0, 0, 0};
		else
			direct_light = sample_direct_lighting(scene, rec, v, info);
		info->final = color_add(info->final, color_prod(info->thru,
					direct_light));
	}
}

static t_bool	handle_emission(t_scene *s, t_hit_record *rec, t_ray *ray,
		t_path_info *i)
{
	t_material	*mat;
	t_real		pdf_light;
	t_real		w;

	mat = rec->object->material;
	if (mat->emission_color.r <= EPSILON && mat->emission_color.g <= EPSILON
		&& mat->emission_color.b <= EPSILON)
		return (FALSE);
	if (i->specular_bounce == TRUE
		|| (s->lights == NULL && s->emissive_lights == NULL))
		w = 1.0;
	else
	{
		pdf_light = compute_emissive_pdf(rec, ray->direction);
		w = power_heuristic(i->last_pdf, pdf_light);
	}
	i->final = color_add(i->final, color_scale(color_prod(i->thru,
					mat->emission_color), w));
	return (TRUE);
}

static t_bool	process_bounce(t_scene *s, t_hit_record *rec, t_ray *ray,
		t_path_info *i)
{
	if (s->render_mode != RENDER_SHADE)
	{
		i->final = debug_pathtracer(s, rec, i, ray);
		return (TRUE);
	}
	if (!rec->object->material)
	{
		i->final = (t_color){0.0, 0.0, 0.0};
		return (TRUE);
	}
	if (handle_emission(s, rec, ray, i))
		return (TRUE);
	apply_surface_logic(s, rec, vec3_scale(ray->direction, -1.0), i);
	i->thru = color_prod(i->thru, get_attenuation(rec->object->material, rec,
				vec3_normalize(vec3_scale(ray->direction, -1.0)), i));
	i->last_pdf = i->pdf;
	if (russian_roulette(i, color_mean(i->thru)) == TRUE)
		return (TRUE);
	return (FALSE);
}

t_color	path_trace(t_scene *s, t_ray ray, unsigned int *seed)
{
	t_path_info		i;
	t_hit_record	rec;

	i.final = (t_color){0.0, 0.0, 0.0};
	i.thru = (t_color){1.0, 1.0, 1.0};
	i.depth = -1;
	i.seed = *seed;
	i.specular_bounce = TRUE;
	i.last_pdf = 1.0;
	i.bvh_root = s->bvh_root;
	while (++i.depth < MAX_REFLECTION_DEPTH)
	{
		if (!hit_bvh(s->bvh_root, &ray, &rec))
			return (color_add(i.final, color_prod(i.thru, get_skybox_color(s,
							&ray))));
		if (process_bounce(s, &rec, &ray, &i) == TRUE)
			break ;
		ray = update_ray(&rec, i.next_dir);
		*seed = i.seed;
	}
	return (i.final);
}
