/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:10:03 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 17:25:30 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	get_ray(t_camera *camera, t_ray *ray, t_real u, t_real v)
{
	t_vec3	target;

	ray->origin = camera->position;
	target = camera->lower_left_corner;
	target = vec3_add(target, vec3_scale(camera->horizontal, u));
	target = vec3_add(target, vec3_scale(camera->vertical, v));
	ray->direction = vec3_sub(target, ray->origin);
	ray->direction = vec3_normalize(ray->direction);
	ray->min = EPSILON;
	ray->max = INFINITY;
}

t_color	get_ray_color(t_scene *scene, t_ray *ray)
{
	t_hit_record record;

	if (hit_objects(scene->objects, ray, &record))
		return (phong_light(scene, &record, ray));
	return ((t_color){0.0, 0.0, 0.0});
}
