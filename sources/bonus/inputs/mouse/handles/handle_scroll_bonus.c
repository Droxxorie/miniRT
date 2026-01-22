/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_scroll_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:04:41 by eraad             #+#    #+#             */
/*   Updated: 2026/01/22 20:24:59 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_bool	handle_scroll(int button, t_scene *s)
{
	int	mode;
	int	dir;

	dir = -1;
	if (button == SCROLL_UP)
		dir = 1;
	mode = RESIZE_UNIFORM;
	if (s->ctrl_pressed == TRUE)
		mode = RESIZE_Z;
	else if (s->shift_pressed == TRUE)
		mode = RESIZE_Y;
	else if (s->alt_pressed == TRUE)
		mode = RESIZE_X;
	if (s->selected_object && s->selected_object->visible != FALSE)
	{
		dispatch_resize(s->selected_object, s->active_camera, mode, dir);
		refresh_bvh(s, s->selected_object);
	}
	else if (s->selected_light == NULL)
		resize_camera_fov(s->active_camera, mode, dir);
	else if (s->selected_light)
		resize_light(s->selected_light, s->active_camera, mode, dir);
	else
		return (FALSE);
	return (TRUE);
}
