/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_scroll_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:04:41 by eraad             #+#    #+#             */
/*   Updated: 2026/01/04 13:04:52 by eraad            ###   ########.fr       */
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
		mode = RESIZE_HEIGHT;
	else
		mode = RESIZE_RADIUS;
	dispatch_resize(scene->selected_object, mode, direction);
	return (TRUE);
}
