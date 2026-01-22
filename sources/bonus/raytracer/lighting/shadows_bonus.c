/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:26:07 by eraad             #+#    #+#             */
/*   Updated: 2026/01/22 15:58:54 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

//* uv_offset[0] = u_offset
//* uv_offset[1] = v_offset
static t_vec3	get_light_sample(t_light *light, t_hit_record *record,
		unsigned int *seed)
{
	t_vec3	random_point;
	t_vec3	uv_offset[2];
	t_vec3	sun_source;
	t_vec3	jitter;
	t_real	r[2];

	if (light->type == LIGHT_SUN)
	{
		sun_source = vec3_scale(light->direction, -10000.0);
		jitter = vec3_scale(random_in_unit_sphere(seed), 50.0);
		return (vec3_add(record->hit_point, vec3_add(sun_source, jitter)));
	}
	else if (light->type == LIGHT_QUAD)
	{
		r[0] = random_double(seed) - 0.5;
		r[1] = random_double(seed) - 0.5;
		uv_offset[0] = vec3_scale(light->u, r[0]);
		uv_offset[1] = vec3_scale(light->v, r[1]);
		return (vec3_add(light->position, vec3_add(uv_offset[0],
					uv_offset[1])));
	}
	random_point = random_in_unit_sphere(seed);
	return (vec3_add(light->position, vec3_scale(random_point, LIGHT_RADIUS)));
}

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
		t_real *attenuation, t_vec3 target)
{
	t_vec3		remain;
	t_material	*mat;

	mat = hit->object->material;
	if (!mat)
		return (FALSE);
	if ((mat->transparency > 0.001 || mat->type == DIELECTRIC)
		|| (mat->emission_color.r > 0.0 || mat->emission_color.g > 0.0
			|| mat->emission_color.b > 0.0))
	{
		if ((mat->transparency > 0.001 || mat->type == DIELECTRIC))
		{
			if (mat->transparency > 0.0)
				*attenuation *= mat->transparency;
			else
				*attenuation *= 0.95;
		}
		ray->origin = ray_at(ray, hit->t + 0.001);
		remain = vec3_sub(target, ray->origin);
		ray->direction = vec3_normalize(remain);
		ray->max = vec3_len(remain);
		return (TRUE);
	}
	return (FALSE);
}

static t_real	cast_shadow_ray(t_scene *scene, t_vec3 target,
		t_hit_record *rec)
{
	t_ray			s_ray;
	t_hit_record	hit;
	t_real			attenuation;
	int				layer;

	attenuation = 1.0;
	s_ray.origin = vec3_add(rec->hit_point, vec3_scale(rec->normal, 0.001));
	s_ray.direction = vec3_sub(target, s_ray.origin);
	s_ray.max = vec3_len(s_ray.direction);
	s_ray.direction = vec3_normalize(s_ray.direction);
	s_ray.min = 0.001;
	s_ray.is_shadow_ray = TRUE;
	layer = 0;
	while (layer < 12 && hit_bvh(scene->bvh_root, &s_ray, &hit))
	{
		if (hit.t > s_ray.max)
			break ;
		if (handle_transparency(&hit, &s_ray, &attenuation, target) == FALSE)
			return (0.0);
		layer++;
	}
	if (hit_sdf_shadow(scene, &s_ray, vec3_len(vec3_sub(target, s_ray.origin))))
		return (0.0);
	return (attenuation);
}

t_real	get_shadow_factor(t_scene *scene, t_hit_record *record, t_light *light)
{
	int				i;
	t_real			visibility;
	t_vec3			target;
	unsigned int	seed;

	seed = generate_seed(record->hit_point);
	if (SHADOW_SAMPLES <= 1)
		return (cast_shadow_ray(scene, light->position, record));
	visibility = 0.0;
	i = 0;
	while (i < SHADOW_SAMPLES)
	{
		target = get_light_sample(light, record, &seed);
		visibility += cast_shadow_ray(scene, target, record);
		i++;
	}
	return (visibility / (t_real)SHADOW_SAMPLES);
}
