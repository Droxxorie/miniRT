/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:20:05 by eraad             #+#    #+#             */
/*   Updated: 2025/12/15 13:24:18 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	resize_cylinder(t_object *object, int key)
{
	t_real	k;

	if (key == KEY_PLUS || key == KEY_MINUS)
	{
		if (key == KEY_PLUS)
			k = STEP_SIZE;
		else
			k = -STEP_SIZE;
		object->data.cylinder.radius += k;
		if (object->data.cylinder.radius < 0.1)
			object->data.cylinder.radius = 0.1;
		object->data.cylinder.radius_squared = object->data.cylinder.radius
			* object->data.cylinder.radius;
	}
	else if (key == KEY_2 || key == KEY_8)
	{
		if (key == KEY_8)
			k = STEP_SIZE;
		else
			k = -STEP_SIZE;
		object->data.cylinder.height += k;
		if (object->data.cylinder.height < 0.1)
			object->data.cylinder.height = 0.1;
	}
}
