/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_scroll_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:04:41 by eraad             #+#    #+#             */
/*   Updated: 2026/01/11 20:03:08 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_bool	handle_scroll(int button, t_scene *scene)
{
	int	mode;
	int	direction;

	if (button == SCROLL_UP)
		direction = 1;
	else
		direction = -1;
	if (scene->ctrl_pressed == TRUE)
		mode = RESIZE_Z;
	else if (scene->shift_pressed == TRUE)
		mode = RESIZE_Y;
	else if (scene->alt_pressed == TRUE)
		mode = RESIZE_X;
	else
		mode = RESIZE_UNIFORM;
	if (scene->selected_object && scene->selected_object->visible != FALSE)
	{
		dispatch_resize(scene->selected_object, mode, direction);
		refresh_bvh(scene, scene->selected_object);
	}
	else if (scene->selected_light == NULL)
		resize_camera_fov(scene->active_camera, mode, direction);
	else
		return (FALSE);
	return (TRUE);
}
