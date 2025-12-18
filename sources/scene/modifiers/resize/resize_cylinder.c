/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:20:05 by eraad             #+#    #+#             */
/*   Updated: 2025/12/18 17:44:44 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	resize_cylinder(t_object *object, int mode, int direction)
{
	t_cylinder	*cylinder;

	cylinder = &object->u_data.cylinder;
	if (mode == RESIZE_RADIUS)
	{
		cylinder->radius += (direction * STEP_SIZE);
		if (cylinder->radius < 0.1)
			cylinder->radius = 0.1;
		cylinder->radius_squared = cylinder->radius * cylinder->radius;
	}
	else if (mode == RESIZE_HEIGHT)
	{
		cylinder->height += (direction * STEP_SIZE);
		if (cylinder->height < 0.1)
			cylinder->height = 0.1;
	}
}
