/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_selection_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:24:12 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 13:24:42 by eraad            ###   ########.fr       */
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
	log_event(stdout, "INFO", "Selected light ID: %d\n",
		scene->selected_light->id);
}

void	action_selection(t_scene *scene, t_vec3 input_vector)
{
	t_vec3	relative_vector;

	relative_vector = get_camera_relative_vector(input_vector,
			scene->active_camera);
	if (scene->selected_object && scene->selected_object->visible == TRUE)
	{
		if (scene->control_mode == TRANSLATE)
			translate_object(scene->selected_object,
				vec3_scale(relative_vector, STEP_MOVE));
		else if (scene->control_mode == ROTATE)
			rotate_object(scene->selected_object,
				vec3_scale(relative_vector, STEP_ROT));
		refresh_bvh(scene, scene->selected_object);
	}
	else if (scene->selected_light && scene->selected_light->active == TRUE)
	{
		if (scene->control_mode == TRANSLATE)
			translate_light(scene->selected_light, vec3_scale(relative_vector,
					STEP_MOVE));
	}
}
