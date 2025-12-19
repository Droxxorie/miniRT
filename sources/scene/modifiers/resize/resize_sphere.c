/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:18:57 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 12:54:19 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	resize_sphere(t_object *object, int mode, int direction)
{
	t_sphere	*sphere;

	sphere = &object->u_data.sphere;
	if (mode == RESIZE_RADIUS)
	{
		sphere->radius += (direction * STEP_SIZE);
		if (sphere->radius < 0.1)
			sphere->radius = 0.1;
	}
}
