/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_camera_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:01:09 by eraad             #+#    #+#             */
/*   Updated: 2026/01/05 21:10:06 by eraad            ###   ########.fr       */
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
	ft_putstr_fd("Switched to camera ID: ", 1);
	ft_putnbr_fd(scene->active_camera->id, 1);
	ft_putstr_fd("\n", 1);
}
