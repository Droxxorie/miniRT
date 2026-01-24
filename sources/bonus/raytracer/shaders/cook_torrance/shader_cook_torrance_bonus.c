/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_cook_torrance_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:07:26 by eraad             #+#    #+#             */
/*   Updated: 2026/01/24 13:10:45 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_color	get_indirect_specular(t_scene *s, t_hit_record *rec,
		t_ray *view_ray, t_cook_torrance_vars *v)
{
	t_vec3			reflected_dir;
	t_vec3			fuzz;
	t_ray			reflected_ray;
	t_color			env_color;
	unsigned int	seed;

	reflected_dir = vec_reflect(vec3_normalize(view_ray->direction),
			rec->normal);
	if (v->roughness > 0.0)
	{
		seed = generate_seed(rec->hit_point);
		fuzz = vec3_scale(random_in_unit_sphere(&seed), v->roughness);
		reflected_dir = vec3_add(reflected_dir, fuzz);
		reflected_dir = vec3_normalize(reflected_dir);
	}
	if (vec3_dot(reflected_dir, rec->normal) <= 0.0)
		return ((t_color){0.0, 0.0, 0.0});
	reflected_ray = new_ray(vec3_add(rec->hit_point, vec3_scale(rec->normal,
					EPSILON)), reflected_dir);
	env_color = cast_ray(s, &reflected_ray, v->depth - 1);
	return (color_prod(env_color, fresnel_schlick(v->n_dot_v, v->f0)));
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

t_color	shader_cook_torrance(t_scene *s, t_hit_record *rec, t_ray *ray,
		int depth)
{
	t_cook_torrance_vars	v;
	t_color					direct_light;
	t_color					indirect_light;
	t_color					ambient;
	t_light					*light;

	init_cook_torrance_vars(&v, rec, ray, depth);
	direct_light = (t_color){0.0, 0.0, 0.0};
	light = s->lights;
	while (light)
	{
		direct_light = color_add(direct_light, process_light(s, light, &v,
					rec));
		light = light->next;
	}
	if (depth > 0)
		indirect_light = get_indirect_specular(s, rec, ray, &v);
	else
		indirect_light = (t_color){0.0, 0.0, 0.0};
	ambient = color_prod(color_prod(s->ambient, v.albedo),
			color_scale(color_sub((t_color){1, 1, 1}, v.f0), 1.0 - v.metallic));
	ambient = color_scale(ambient, compute_ao(s, rec));
	return (color_add(color_add(direct_light, indirect_light), ambient));
}
