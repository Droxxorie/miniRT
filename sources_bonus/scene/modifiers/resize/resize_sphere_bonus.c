/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_sphere_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:18:57 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:43:39 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_sphere(t_object *object, int mode, int direction)
{
	t_sphere	*sphere;

	if (mode == RESIZE_RADIUS)
	{
		sphere = &object->u_data.sphere;
		sphere->radius += (direction * STEP_SIZE);
		if (sphere->radius < 0.1)
			sphere->radius = 0.1;
		update_object_matrix(object);
	}
}
