/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:16:27 by eraad             #+#    #+#             */
/*   Updated: 2026/01/05 22:53:55 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_vec3	get_camera_relative_vector(t_vec3 input, t_camera *camera)
{
	t_vec3	direction;
	t_vec3	camera_up;
	t_vec3	camera_right;
	t_vec3	camera_forward;

	camera_up = (t_vec3){camera->camera_to_world.m[1][0],
		camera->camera_to_world.m[1][1],
		camera->camera_to_world.m[1][2]};
	camera_forward = (t_vec3){camera->camera_to_world.m[2][0],
		camera->camera_to_world.m[2][1],
		camera->camera_to_world.m[2][2]};
	camera_right = (t_vec3){camera->camera_to_world.m[0][0],
		camera->camera_to_world.m[0][1],
		camera->camera_to_world.m[0][2]};
	direction = (t_vec3){0.0, 0.0, 0.0};
	direction = vec3_add(direction, vec3_scale(camera_forward, input.x));
	direction = vec3_add(direction, vec3_scale(camera_right, input.z));
	direction = vec3_add(direction, vec3_scale(camera_up, input.y));
	return (direction);
}

void	action_selection(t_scene *scene, t_vec3 input_vector)
{
	t_vec3	relative_vector;

	relative_vector = get_camera_relative_vector(input_vector,
			scene->active_camera);
	if (scene->selected_object)
	{
		if (scene->control_mode == TRANSLATE)
			dispatch_translate(scene->selected_object,
				vec3_scale(relative_vector, STEP_MOVE));
		else if (scene->control_mode == ROTATE)
			dispatch_rotate(scene->selected_object, vec3_scale(relative_vector,
					STEP_ROT));
	}
	else if (scene->selected_light)
	{
		if (scene->control_mode == TRANSLATE)
			translate_light(scene->selected_light, vec3_scale(relative_vector,
					STEP_MOVE));
	}
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
