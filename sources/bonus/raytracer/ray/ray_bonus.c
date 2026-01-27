/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:37:00 by eraad             #+#    #+#             */
/*   Updated: 2026/01/24 15:29:02 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_ray	new_ray(t_point3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vec3_normalize(direction);
	ray.min = EPSILON;
	ray.max = INFINITY;
	ray.is_shadow_ray = FALSE;
	return (ray);
}

t_ray	transform_ray(t_ray ray, t_mat4 inverse)
{
	t_ray	local_ray;

	local_ray.origin = mat4_mult_point3(inverse, ray.origin);
	local_ray.direction = mat4_mult_vec3(inverse, ray.direction);
	local_ray.min = ray.min;
	local_ray.max = ray.max;
	return (local_ray);
}

t_color	cast_ray(t_scene *scene, t_ray *ray, int depth)
{
	t_hit_record	record;

	if (depth <= 0)
		return ((t_color){0.0, 0.0, 0.0});
	if (hit_bvh(scene->bvh_root, ray, &record))
	{
		if (scene->render_mode != RENDER_SHADE)
			return (render_debug(scene, &record));
		else
			return (render_whitted(scene, &record, ray, depth));
	}
	return (get_skybox_color(scene, ray));
}

void	generate_ray(t_camera *camera, t_ray *ray, t_real x, t_real y)
{
	t_real	px;
	t_real	py;
	t_vec3	local_dir;
	t_vec3	world_dir;

	px = (2.0 * ((x + 0.5) / camera->width) - 1.0) * camera->aspect_ratio
		* camera->scale_factor;
	py = (1.0 - 2.0 * ((y + 0.5) / camera->height)) * camera->scale_factor;
	local_dir = (t_vec3){px, py, -1.0};
	world_dir = mat4_mult_vec3(camera->camera_to_world, local_dir);
	*ray = new_ray(camera->position, world_dir);
}
