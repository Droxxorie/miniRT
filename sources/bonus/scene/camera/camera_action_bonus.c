/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_action_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:22:21 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 13:23:19 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	action_camera(t_scene *scene, t_vec3 input_vector)
{
	t_real	aspect_ratio;

	aspect_ratio = scene->mlx_window.aspect_ratio;
	if (scene->control_mode == TRANSLATE)
		translate_camera(scene->active_camera, vec3_scale(input_vector,
				STEP_MOVE), aspect_ratio);
	else if (scene->control_mode == ROTATE)
		rotate_camera(scene->active_camera, vec3_scale(input_vector, STEP_ROT),
			aspect_ratio);
}

void	switch_camera_next(t_scene *scene)
{
	if (!scene || !scene->cameras)
		return ;
	if (scene->active_camera->next)
		scene->active_camera = scene->active_camera->next;
	else
		scene->active_camera = scene->cameras;
	log_event(stdout, "INFO", "Switched camera\n");
	log_camera_info(scene->active_camera);
}
