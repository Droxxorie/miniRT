/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:13:31 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 11:13:32 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_bool	handle_transform_keys(int key, t_scene *scene)
{
	t_vec3	input_vector;

	input_vector = get_input_vector(key);
	if (vec3_len_squared(input_vector) < EPSILON)
		return (FALSE);
	if (scene->selected_object || scene->selected_light)
		action_selection(scene, input_vector);
	else
		action_camera(scene, input_vector);
	return (TRUE);
}

static t_bool	handle_resize_keys(int key, t_scene *scene)
{
	if (key == KEY_PLUS || key == KEY_MINUS || key == KEY_2 || key == KEY_8)
	{
		if (scene->selected_object)
		{
			dispatch_resize(scene->selected_object, key);
			return (TRUE);
		}
	}
	return (FALSE);
}

static t_bool	handle_state_keys(int key, t_scene *scene)
{
	if (key == KEY_ESC)
		clean_exit(scene, EXIT_SUCCESS);
	if (key == KEY_TAB)
	{
		if (scene->control_mode == TRANSLATE)
		{
			scene->control_mode = ROTATE;
			ft_putstr_fd("Mode: ROTATE\n", STDOUT_FILENO);
		}
		else
		{
			scene->control_mode = TRANSLATE;
			ft_putstr_fd("Mode: TRANSLATE\n", STDOUT_FILENO);
		}
		return (FALSE);
	}
	if (key == KEY_SPACE)
	{
		switch_camera_next(scene);
		return (TRUE);
	}
	return (FALSE);
}

int	key_hook(int key, t_scene *scene)
{
	t_bool	render_needed;

	render_needed = FALSE;
	if (handle_state_keys(key, scene) == TRUE)
		render_needed = TRUE;
	if (handle_resize_keys(key, scene) == TRUE)
		render_needed = TRUE;
	if (handle_transform_keys(key, scene) == TRUE)
		render_needed = TRUE;
	if (render_needed == TRUE)
		render_scene(scene);
	return (EXIT_SUCCESS);
}
