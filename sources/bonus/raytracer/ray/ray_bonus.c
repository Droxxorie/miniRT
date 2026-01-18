/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:37:00 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 19:00:29 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_ray	transform_ray(t_ray ray, t_mat4 inverse)
{
	t_ray	local_ray;

	local_ray.origin = mat4_mult_point3(inverse, ray.origin);
	local_ray.direction = mat4_mult_vec3(inverse, ray.direction);
	local_ray.min = ray.min;
	local_ray.max = ray.max;
	return (local_ray);
}

t_color	compute_pixel_color(t_scene *scene, t_ray *ray)
{
	t_hit_record	record;
	t_real			ao_factor;

	if (hit_bvh(scene->bvh_root, ray, &record))
	{
		if (scene->render_mode == RENDER_NORMAL)
			return ((t_color){(record.normal.x + 1.0) * 0.5, (record.normal.y
					+ 1.0) * 0.5, (record.normal.z + 1.0) * 0.5});
		else if (scene->render_mode == RENDER_AO)
		{
			ao_factor = compute_ao(scene, &record);
			return ((t_color){ao_factor, ao_factor, ao_factor});
		}
		else
			return (phong_light(scene, &record, ray));
	}
	return ((t_color){0.0, 0.0, 0.0});
}

void	generate_ray(t_camera *camera, t_ray *ray, t_real x, t_real y)
{
	t_real	px;
	t_real	py;
	t_vec3	local_direction;

	px = (2.0 * ((x + 0.5) / camera->width) - 1.0) * camera->aspect_ratio
		* camera->scale_factor;
	py = (1.0 - 2.0 * ((y + 0.5) / camera->height)) * camera->scale_factor;
	local_direction = (t_vec3){px, py, -1.0};
	ray->origin = camera->position;
	ray->direction = vec3_normalize(mat4_mult_vec3(camera->camera_to_world,
				local_direction));
	ray->min = EPSILON;
	ray->max = INFINITY;
	ray->is_shadow_ray = FALSE;
}
