/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_cook_torrance_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:07:26 by eraad             #+#    #+#             */
/*   Updated: 2026/01/24 11:11:11 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	init_cook_torrance_vars(t_cook_torrance_vars *v, t_hit_record *rec,
		t_ray *ray)
{
	t_material	*mat;

	mat = rec->object->material;
	v->n = rec->normal;
	v->v = vec3_scale(ray->direction, -1.0);
	v->n_dot_v = fmax(vec3_dot(v->n, v->v), 0.0);
	v->albedo = get_albedo(mat, rec);
	v->roughness = mat->roughness;
	v->metallic = mat->metallic;
	if (mat->roughness_map)
		v->roughness = sample_texture(mat->roughness_map, rec->u, rec->v).r;
	if (mat->metallic_map)
		v->metallic = sample_texture(mat->metallic_map, rec->u, rec->v).r;
	v->f0 = (t_color){0.04, 0.04, 0.04};
	if (color_mean(mat->specular_color) > EPSILON)
		v->f0 = mat->specular_color;
	else if (v->metallic > 0.5)
		v->f0 = v->albedo;
}

static t_color	compute_brdf(t_cook_torrance_vars *v, t_color *k_s)
{
	t_real	d;
	t_real	g;
	t_color	f;
	t_real	denom;
	t_color	specular;

	d = distribution_ggx(v->n, v->h, v->roughness);
	g = geometry_smith(v->n, v->v, v->l, v->roughness);
	f = fresnel_schlick(fmax(vec3_dot(v->h, v->v), 0.0), v->f0);
	*k_s = f;
	denom = 4.0 * v->n_dot_v * v->n_dot_l;
	specular = color_scale(f, (d * g));
	return (color_div(specular, fmax(denom, 0.001)));
}

static t_color	calculate_lighting(t_cook_torrance_vars *v, t_color k_s,
		t_color radiance)
{
	t_color	diffuse;
	t_color	specular;
	t_color	k_d;

	specular = compute_brdf(v, &k_s);
	k_d = color_scale(color_sub((t_color){1.0, 1.0, 1.0}, k_s), 1.0
			- v->metallic);
	diffuse = color_prod(k_d, color_scale(v->albedo, INV_PI));
	return (color_prod(color_add(diffuse, specular), color_scale(radiance,
				v->n_dot_l)));
}

static t_color	process_light(t_scene *s, t_light *light,
		t_cook_torrance_vars *v, t_hit_record *rec)
{
	t_color	radiance;
	t_color	k_s;
	t_real	dist;
	t_real	shadow;
	t_real	attenuation;

	v->l = vec3_sub(light->position, rec->hit_point);
	dist = vec3_len(v->l);
	v->l = vec3_normalize(v->l);
	v->h = vec3_normalize(vec3_add(v->v, v->l));
	v->n_dot_l = fmax(vec3_dot(v->n, v->l), 0.0);
	if (v->n_dot_l < EPSILON)
		return ((t_color){0.0, 0.0, 0.0});
	shadow = get_shadow_factor(s, rec, light);
	attenuation = get_light_attenuation(light, dist) * get_spot_factor(light,
			v->l);
	radiance = color_scale(light->color, light->brightness * shadow
			* attenuation);
	return (calculate_lighting(v, k_s, radiance));
}

t_color	shader_cook_torrance(t_scene *s, t_hit_record *rec, t_ray *ray)
{
	t_cook_torrance_vars	v;
	t_color					total_light;
	t_color					ambient;
	t_light					*light;

	init_cook_torrance_vars(&v, rec, ray);
	total_light = (t_color){0.0, 0.0, 0.0};
	light = s->lights;
	while (light)
	{
		total_light = color_add(total_light, process_light(s, light, &v, rec));
		light = light->next;
	}
	ambient = color_scale(color_prod(s->ambient, v.albedo), compute_ao(s, rec));
	return (color_add(ambient, total_light));
}
