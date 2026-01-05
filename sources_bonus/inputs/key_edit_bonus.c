/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_edit_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:45:31 by eraad             #+#    #+#             */
/*   Updated: 2026/01/05 22:50:11 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	switch_light_next(t_scene *scene)
{
	if (!scene || !scene->lights)
		return ;
	if (scene->selected_light == NULL)
		scene->selected_light = scene->lights;
	else if (scene->selected_light->next)
		scene->selected_light = scene->selected_light->next;
	else
		scene->selected_light = scene->lights;
	ft_putstr_fd("Light ID: ", 1);
	ft_putnbr_fd(scene->selected_light->id, 1);
	ft_putstr_fd("\n", 1);
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
		else
			ft_putstr_fd("Light rotation not supported\n", STDOUT_FILENO);
	}
}
