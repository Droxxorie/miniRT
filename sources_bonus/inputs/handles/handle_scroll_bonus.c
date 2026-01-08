/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_scroll_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:04:41 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 20:29:48 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_bool	handle_scroll(int button, t_scene *scene)
{
	int	mode;
	int	direction;

	if (scene->selected_object == NULL)
		return (FALSE);
	if (button == SCROLL_UP)
		direction = 1;
	else if (button == SCROLL_DOWN)
		direction = -1;
	else
		return (FALSE);
	if (scene->shift_pressed == TRUE)
		mode = RESIZE_X;
	else if (scene->ctrl_pressed == TRUE)
		mode = RESIZE_Y;
	else
		mode = RESIZE_Z;
	dispatch_resize(scene->selected_object, mode, direction);
	return (TRUE);
}
