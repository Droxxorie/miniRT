/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:13:31 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 20:59:27 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_bool	handle_transform_keys(int key, t_scene *scene)
{
	t_vec3	input_vector;

	input_vector = get_input_vector(key);
	if (vec3_len_squared(input_vector) < EPSILON)
		return (FALSE);
	if (scene->selected_object || scene->selected_light)
	{
		action_selection(scene, input_vector);
		if (scene->selected_object && scene->selected_object->type == SPHERE
			&& scene->control_mode == ROTATE)
			return (FALSE);
		else if (scene->selected_light && scene->control_mode == ROTATE)
			return (FALSE);
	}
	else
		action_camera(scene, input_vector);
	return (TRUE);
}

static void	handle_tab_key(t_scene *scene)
{
	if (scene->control_mode == TRANSLATE)
	{
		scene->control_mode = ROTATE;
		if (scene->selected_object && scene->selected_object->type == SPHERE)
			ft_putstr_fd("Warning: Spheres cannot be rotated.\n",
				STDOUT_FILENO);
		else if (scene->selected_light)
			ft_putstr_fd("Warning: Lights cannot be rotated.\n", STDOUT_FILENO);
		else
			ft_putstr_fd("Mode: ROTATE\n", STDOUT_FILENO);
	}
	else
	{
		scene->control_mode = TRANSLATE;
		ft_putstr_fd("Mode: TRANSLATE\n", STDOUT_FILENO);
	}
}

static t_bool	handle_state_keys(int key, t_scene *scene)
{
	if (key == KEY_ESC)
		clean_exit(scene, EXIT_SUCCESS);
	if (key == KEY_SHIFT_L || key == KEY_SHIFT_R)
	{
		scene->shift_pressed = TRUE;
		return (FALSE);
	}
	if (key == KEY_TAB)
		return (handle_tab_key(scene), FALSE);
	if (key == KEY_SPACE && scene->cameras->id > 1)
		return (switch_camera_next(scene), TRUE);
	if (key == KEY_L && scene->selected_light == NULL)
	{
		scene->selected_light = scene->lights;
		scene->selected_object = NULL;
		ft_putstr_fd("Switched to light control mode\n", 1);
	}
	return (FALSE);
}

int	key_hook(int key, t_scene *scene)
{
	t_bool	render_needed;

	render_needed = FALSE;
	if (handle_state_keys(key, scene) == TRUE)
		render_needed = TRUE;
	if (handle_transform_keys(key, scene) == TRUE)
		render_needed = TRUE;
	if (render_needed == TRUE)
		render_frame(scene);
	return (EXIT_SUCCESS);
}
