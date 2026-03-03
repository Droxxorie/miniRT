/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:26:07 by eraad             #+#    #+#             */
/*   Updated: 2026/01/24 18:29:04 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_bool	hit_sdf_shadow(t_scene *scene, t_ray *ray, t_real max_dist)
{
	t_real	t;
	t_real	h;
	int		steps;

	t = ray->min;
	steps = 0;
	while (t < max_dist && steps < SDF_MAX_STEPS)
	{
		h = map_the_world(ray_at(ray, t), scene);
		if (h < 0.001)
			return (TRUE);
		t += h;
		steps++;
	}
	return (FALSE);
}

static t_bool	handle_transparency(t_hit_record *hit, t_ray *ray,
		t_color *attenuation, t_vec3 target)
{
	t_material	*mat;

	mat = hit->object->material;
	if (!mat)
		return (FALSE);
	if (mat->type == DIELECTRIC || mat->transparency > 0.001
		|| color_mean(mat->emission_color) > EPSILON)
	{
		if (mat->type == DIELECTRIC)
			*attenuation = beer_lambert(*attenuation, hit->t,
					mat->absorbance);
		else if (mat->transparency > 0.001)
			*attenuation = color_scale(*attenuation, mat->transparency);
		ray->origin = ray_at(ray, hit->t + 0.001);
		ray->direction = vec3_normalize(vec3_sub(target, ray->origin));
		ray->max = vec3_len(vec3_sub(target, ray->origin));
		return (TRUE);
	}
	return (FALSE);
}

static t_color	cast_shadow_ray(t_scene *scene, t_vec3 target,
		t_hit_record *rec)
{
	t_ray			s_ray;
	t_hit_record	hit;
	t_color			attenuation;
	int				layer;

	attenuation = (t_color){1.0, 1.0, 1.0};
	s_ray.origin = vec3_add(rec->hit_point, vec3_scale(rec->normal, 0.001));
	s_ray.direction = vec3_normalize(vec3_sub(target, s_ray.origin));
	s_ray.max = vec3_len(vec3_sub(target, s_ray.origin));
	s_ray.min = 0.001;
	s_ray.is_shadow_ray = TRUE;
	layer = 0;
	while (layer < 12 && hit_bvh(scene->bvh_root, &s_ray, &hit))
	{
		if (hit.t > s_ray.max)
			break ;
		if (handle_transparency(&hit, &s_ray, &attenuation, target) == FALSE)
			return ((t_color){0.0, 0.0, 0.0});
		layer++;
	}
	if (hit_sdf_shadow(scene, &s_ray, vec3_len(vec3_sub(target, s_ray.origin))))
		return ((t_color){0.0, 0.0, 0.0});
	return (attenuation);
}

t_color	get_shadow_factor(t_scene *scene, t_hit_record *record, t_light *light)
{
	int				i;
	t_color			visibility;
	t_vec3			target;
	unsigned int	seed;

	seed = generate_seed(record->hit_point);
	if (SHADOW_SAMPLES <= 1)
		return (cast_shadow_ray(scene, light->position, record));
	visibility = (t_color){0.0, 0.0, 0.0};
	i = 0;
	while (i < SHADOW_SAMPLES)
	{
		target = get_light_sample(light, record, &seed);
		visibility = color_add(visibility, cast_shadow_ray(scene, target,
					record));
		i++;
	}
	return (color_scale(visibility, 1.0 / (t_real)SHADOW_SAMPLES));
}
