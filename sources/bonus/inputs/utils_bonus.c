/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:16:27 by eraad             #+#    #+#             */
/*   Updated: 2026/01/29 10:04:04 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_vec3	get_camera_relative_vector(t_vec3 input, t_camera *camera)
{
	t_vec3	direction;
	t_vec3	camera_up;
	t_vec3	camera_right;
	t_vec3	camera_forward;

	camera_right = (t_vec3){camera->camera_to_world.m[0][0],
		camera->camera_to_world.m[0][1],
		camera->camera_to_world.m[0][2]};
	camera_up = (t_vec3){camera->camera_to_world.m[1][0],
		camera->camera_to_world.m[1][1],
		camera->camera_to_world.m[1][2]};
	camera_forward = (t_vec3){camera->camera_to_world.m[2][0],
		camera->camera_to_world.m[2][1],
		camera->camera_to_world.m[2][2]};
	direction = (t_vec3){0.0, 0.0, 0.0};
	direction = vec3_add(direction, vec3_scale(camera_right, input.x));
	direction = vec3_add(direction, vec3_scale(camera_up, input.y));
	direction = vec3_add(direction, vec3_scale(camera_forward, input.z));
	return (direction);
}

t_vec3	get_input_vector(int key)
{
	t_vec3	input_vector;

	input_vector = (t_vec3){0.0, 0.0, 0.0};
	if (key == KEY_UP || key == KEY_Z)
		input_vector.z = -1;
	if (key == KEY_DOWN || key == KEY_S)
		input_vector.z = 1;
	if (key == KEY_LEFT || key == KEY_Q)
		input_vector.x = -1;
	if (key == KEY_RIGHT || key == KEY_D)
		input_vector.x = 1;
	if (key == KEY_A)
		input_vector.y = 1;
	if (key == KEY_E)
		input_vector.y = -1;
	return (input_vector);
}
