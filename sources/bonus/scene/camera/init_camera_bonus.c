/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:13:06 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 12:49:15 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	prepare_cameras(t_scene *scene)
{
	t_camera	*current;
	int			count;

	log_event(stdout, "INFO", "Preparing cameras...\n");
	if (scene == NULL || scene->cameras == NULL)
		return ;
	current = scene->cameras;
	count = 0;
	while (current)
	{
		current->width = scene->mlx_window.width;
		current->height = scene->mlx_window.height;
		current->aspect_ratio = (t_real)current->width
			/ (t_real)current->height;
		update_camera(current, scene->mlx_window.aspect_ratio);
		current->id = ++count;
		current = current->next;
	}
	scene->active_camera = scene->cameras;
	log_event(stdout, "SUCCESS", "Cameras ready!\n");
}
