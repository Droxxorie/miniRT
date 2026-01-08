/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_r_key_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:46:52 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 16:34:42 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	handle_r_key(t_scene *scene)
{
	if (scene->shift_pressed == TRUE)
	{
		log_event(stdout, "WARN", "Resetting scene to initial state");
		reset_scene_state(scene);
	}
	else
	{
		if (scene->selected_object)
		{
			log_event(stdout, "WARN", "Resetting object state");
			reset_object_state(scene->selected_object);
		}
		else if (scene->selected_light)
		{
			log_event(stdout, "WARN", "Resetting light state");
			reset_light_state(scene->selected_light);
		}
		else if (scene->active_camera)
		{
			log_event(stdout, "WARN", "Resetting active camera state");
			reset_camera_state(scene->active_camera);
		}
	}
}
