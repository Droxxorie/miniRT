/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_camera_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:32:37 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 19:54:45 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_camera_fov(t_camera *camera, int mode, int direction)
{
	t_real	new_fov;
	int		current_fov;

	(void)mode;
	current_fov = camera->fov;
	if (direction < 0)
		new_fov = (t_real)current_fov * 1.1;
	else
		new_fov = (t_real)current_fov * 0.9;
	if (direction < 0 && (int)new_fov <= current_fov)
		new_fov = current_fov + 1.0;
	else if (direction > 0 && (int)new_fov >= current_fov)
		new_fov = current_fov - 1.0;
	if (new_fov < 1.0)
		new_fov = 1.0;
	else if (new_fov > 179.0)
		new_fov = 179.0;
	if ((int)new_fov != current_fov)
	{
		camera->fov = (int)new_fov;
		log_event(stdout, "INFO", "Camera %d FOV resized to %d degrees.",
			camera->id, camera->fov);
		update_camera(camera, camera->aspect_ratio);
	}
}
