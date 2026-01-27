/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light_contribution_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:40:55 by eraad             #+#    #+#             */
/*   Updated: 2026/01/27 17:02:29 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

//* PDF = distance^2 / (area * cos_theta)
t_real	light_pdf(t_light *light, t_hit_record *rec, t_vec3 light_dir)
{
	t_real	dist_sq;
	t_real	area;
	t_real	cos_light;

	if (light->type == LIGHT_SUN)
		return (1.0);
	dist_sq = vec3_len_squared(vec3_sub(light->position, rec->hit_point));
	cos_light = 1.0;
	if (light->type == LIGHT_QUAD)
	{
		area = light->width * light->height;
		cos_light = vec3_dot(light_dir, vec3_scale(light->direction, -1.0));
		if (cos_light <= 0.001)
			cos_light = 0.0;
	}
	else
		area = 4.0 * PI * LIGHT_RADIUS * LIGHT_RADIUS;
	if (area < EPSILON)
		area = 1.0;
	return (dist_sq / (area * cos_light + EPSILON));
}

void	get_light_geometry(t_light *light, t_hit_record *record,
		unsigned int *seed, t_light_sample_vars *vars)
{
	vars->light_pos = get_light_sample(light, record, seed);
	vars->light_dir = vec3_sub(vars->light_pos, record->hit_point);
	vars->dist = INFINITY;
	if (light->type != LIGHT_SUN)
		vars->dist = vec3_len(vars->light_dir);
	vars->light_dir = vec3_normalize(vars->light_dir);
}

static t_color	get_incoming_light(t_light *l, t_vec3 light_dir)
{
	t_color	intensity;

	intensity = color_scale(l->color, l->brightness);
	intensity = color_scale(intensity, get_spot_factor(l, vec3_scale(light_dir,
					-1.0)));
	return (intensity);
}

static t_bool	is_occulted(t_path_info *i, t_hit_record *rec,
		t_light_sample_vars *v)
{
	t_ray			shadow_ray;
	t_hit_record	shadow_rec;

	shadow_ray = new_ray(vec3_add(rec->hit_point, vec3_scale(rec->normal, 0.1)),
			v->light_dir);
	shadow_ray.min = 0.01;
	shadow_ray.is_shadow_ray = TRUE;
	shadow_ray.max = v->dist - 0.1;
	if (hit_bvh(i->bvh_root, &shadow_ray, &shadow_rec))
		if (shadow_rec.object->material->emission_color.r < EPSILON)
			return (TRUE);
	return (FALSE);
}

t_color	compute_light_contribution(t_light *l, t_hit_record *rec, t_vec3 v,
		t_path_info *info)
{
	t_light_sample_vars	s;
	t_real				n_dot_l;
	t_real				pdf_val;
	t_color				intensity;
	t_color				result;

	get_light_geometry(l, rec, &info->seed, &s);
	if (is_occulted(info, rec, &s))
		return ((t_color){0.0, 0.0, 0.0});
	n_dot_l = fmax(vec3_dot(rec->normal, s.light_dir), 0.0);
	if (n_dot_l <= EPSILON)
		return ((t_color){0.0, 0.0, 0.0});
	pdf_val = light_pdf(l, rec, s.light_dir);
	if (pdf_val < EPSILON)
		return ((t_color){0, 0, 0});
	s.f_r = eval_bsdf(rec->object->material, rec, v, s.light_dir);
	intensity = get_incoming_light(l, s.light_dir);
	s.weight = 1.0;
	if (l->type != LIGHT_SUN)
		s.weight = power_heuristic(pdf_val, bsdf_pdf(rec->object->material,
					rec->normal, v, s.light_dir));
	result = color_prod(s.f_r, intensity);
	result = color_scale(result, n_dot_l * s.weight / pdf_val);
	return (result);
}
