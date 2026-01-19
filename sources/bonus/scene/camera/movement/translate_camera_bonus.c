/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_camera_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 08:23:58 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 12:47:54 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	translate_camera(t_camera *camera, t_vec3 input_scaled,
		t_real aspect_ratio)
{
	t_vec3	translation;
	t_vec3	right;
	t_vec3	up;
	t_vec3	forward;
	t_real	speed;

	right = (t_vec3){camera->camera_to_world.m[0][0],
		camera->camera_to_world.m[1][0], camera->camera_to_world.m[2][0]};
	up = (t_vec3){camera->camera_to_world.m[0][1],
		camera->camera_to_world.m[1][1], camera->camera_to_world.m[2][1]};
	forward = (t_vec3){camera->camera_to_world.m[0][2],
		camera->camera_to_world.m[1][2], camera->camera_to_world.m[2][2]};
	speed = camera->scale_factor * MOVE_SPEED;
	translation = (t_vec3){0, 0, 0};
	input_scaled = vec3_scale(input_scaled, speed);
	translation = vec3_add(translation, vec3_scale(right, input_scaled.x));
	translation = vec3_add(translation, vec3_scale(up, input_scaled.y));
	translation = vec3_add(translation, vec3_scale(forward, input_scaled.z));
	camera->position = vec3_add(camera->position, translation);
	update_camera(camera, aspect_ratio);
}
