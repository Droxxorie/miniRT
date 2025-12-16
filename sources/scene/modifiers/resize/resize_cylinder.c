/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:20:05 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 19:09:07 by eraad            ###   ########.fr       */
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
		object->u_data.cylinder.radius += k;
		if (object->u_data.cylinder.radius < 0.1)
			object->u_data.cylinder.radius = 0.1;
		object->u_data.cylinder.radius_squared = object->u_data.cylinder.radius
			* object->u_data.cylinder.radius;
	}
	else if (key == KEY_2 || key == KEY_8)
	{
		if (key == KEY_8)
			k = STEP_SIZE;
		else
			k = -STEP_SIZE;
		object->u_data.cylinder.height += k;
		if (object->u_data.cylinder.height < 0.1)
			object->u_data.cylinder.height = 0.1;
	}
}
