/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:38:24 by eraad             #+#    #+#             */
/*   Updated: 2026/01/15 17:56:26 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_real	compute_soft_shadow(t_ray *ray, t_real t_max, t_real k,
		t_scene *scene)
{
	t_real	result;
	t_real	t;
	t_real	dist;
	t_real	prev_dist;
	t_real	var[2];

	result = 1.0;
	t = ray->min;
	prev_dist = 1e20;
	while (t < t_max)
	{
		dist = map_the_world(ray_at(ray, t), scene);
		if (dist < 0.001)
			return (0.0);
		var[0] = dist * dist / (2.0 * prev_dist);
		var[1] = sqrt(dist * dist - var[0] * var[0]);
		result = fmin(result, k * var[1] / fmax(0.0, t - var[0]));
		prev_dist = dist;
		t += dist;
	}
	return (ft_clamp(result, 0.0, 1.0));
}

t_real	get_shadow_factor(t_scene *scene, t_hit_record *record, t_light *light)
{
	t_vec3	dir_to_light;
	t_real	dist_to_light;
	t_ray	shadow_ray;
	t_real	noise;

	dir_to_light = vec3_sub(light->position, record->hit_point);
	dist_to_light = vec3_len(dir_to_light);
	shadow_ray.direction = vec3_normalize(dir_to_light);
	noise = noise_3d(record->hit_point);
	shadow_ray.origin = vec3_add(record->hit_point, vec3_scale(record->normal,
				SHADOW_BIAS + (noise * SHADOW_NOISE)));
	shadow_ray.min = SDF_THICKNESS;
	shadow_ray.max = dist_to_light;
	return (compute_soft_shadow(&shadow_ray, dist_to_light, SHADOW_HARDNESS,
			scene));
}
