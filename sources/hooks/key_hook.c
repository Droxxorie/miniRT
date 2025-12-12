/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:56:16 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 23:18:42 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_vec3	get_input_vector(int key)
{
	t_vec3	input_vector;

	input_vector = (t_vec3){0.0, 0.0, 0.0};
	if (key == KEY_UP || key == KEY_W || key == KEY_Z)
		input_vector.y = 1;
	if (key == KEY_DOWN || key == KEY_S)
		input_vector.y = -1;
	if (key == KEY_LEFT || key == KEY_A || key == KEY_Q)
		input_vector.x = -1;
	if (key == KEY_RIGHT || key == KEY_D)
		input_vector.x = 1;
	//TODO ajouter avant et arriere
	return (input_vector);
}

int	key_hook(int key, t_scene *scene)
{
	t_vec3	input_vector;
	t_bool	updated;

	updated = FALSE;
	if (key == KEY_ESC)
		clean_exit(scene, EXIT_SUCCESS);
	if (key == KEY_TAB)
	{
		if (scene->control_mode == TRANSLATE)
		{
			scene->control_mode = ROTATE;
			log_info("Switched to ROTATE mode");
		}
		else if (scene->control_mode == ROTATE)
		{
			scene->control_mode = TRANSLATE;
			log_info("Switched to TRANSLATE mode");
		}
	}
	if (key == KEY_SPACE)
	{
		switch_camera_next(scene); //TODO
		return (EXIT_SUCCESS);
	}
	if (key == KEY_PLUS || key == KEY_MINUS)
	{
		if (scene->selected_object)
		{
			resize_object(scene->selected_object, key);
			updated = TRUE;
		}
	}
	input_vector = get_input_vector(key);
	if (vec3_len_squared(input_vector) > 0)
	{
		if (scene->selected_object)
		{
			if (scene->control_mode == TRANSLATE)
				translate_object(scene->selected_object, vec3_scale(input_vector, STEP_MOVE));
			else if (scene->control_mode == ROTATE)
				rotate_object(scene->selected_object, vec3_scale(input_vector, STEP_ROT));
		}
		else
		{
			if (scene->control_mode == TRANSLATE)
				translate_camera(scene->active_camera, vec3_scale(input_vector, STEP_MOVE));
			else if (scene->control_mode == ROTATE)
				rotate_camera(scene->active_camera, vec3_scale(input_vector, STEP_ROT));
		}
		updated = TRUE;
	}
	if (updated)
		render_frame(scene);
	return (EXIT_SUCCESS);
}
