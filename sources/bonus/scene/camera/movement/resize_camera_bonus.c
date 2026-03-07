/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_camera_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:32:37 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 11:28:29 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_camera_fov(t_camera *camera, int mode, int direction)
{
	t_real	delta;
	t_real	step;

	(void)mode;
	step = 2.0;
	if (direction < 0)
		delta = step;
	else
		delta = -step;
	camera->fov += delta;
	if (camera->fov < 1.0)
		camera->fov = 1.0;
	else if (camera->fov > 179.0)
		camera->fov = 179.0;
	camera->scale_factor = tanf((camera->fov * PI / 180.0) * 0.5);
}
