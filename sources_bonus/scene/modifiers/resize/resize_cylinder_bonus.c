/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_cylinder_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:20:05 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:43:36 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_cylinder(t_object *object, int mode, int direction)
{
	t_cylinder	*cylinder;
	t_real		change;

	cylinder = &object->u_data.cylinder;
	change = direction * STEP_SIZE;
	if (mode == RESIZE_RADIUS)
	{
		cylinder->radius += change;
		if (cylinder->radius < 0.1)
			cylinder->radius = 0.1;
	}
	else if (mode == RESIZE_HEIGHT)
	{
		cylinder->height += change;
		if (cylinder->height < 0.1)
			cylinder->height = 0.1;
	}
	update_object_matrix(object);
}
