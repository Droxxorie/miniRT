/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_rectangle_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:25:10 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 08:55:43 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_rectangle(t_object *object, int mode, int direction)
{
	t_rectangle	*rectangle;
	t_real		change;

	rectangle = &object->u_data.rectangle;
	change = direction * STEP_SIZE;
	if (mode == RESIZE_X)
	{
		rectangle->width += change;
		if (rectangle->width < 0.1)
			rectangle->width = 0.1;
		log_event(stdout, "INFO", "Rectangle width resized to %.2f",
			rectangle->width);
		update_object(object);
	}
	else if (mode == RESIZE_Y)
	{
		rectangle->height += change;
		if (rectangle->height < 0.1)
			rectangle->height = 0.1;
		log_event(stdout, "INFO", "Rectangle height resized to %.2f",
			rectangle->height);
		update_object(object);
	}
}
