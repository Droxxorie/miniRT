/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_sphere_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:18:57 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 08:55:46 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_sphere(t_object *object, int mode, int direction)
{
	t_sphere	*sphere;

	if (mode == RESIZE_X)
	{
		sphere = &object->u_data.sphere;
		sphere->radius += (direction * STEP_SIZE);
		if (sphere->radius < 0.1)
			sphere->radius = 0.1;
		log_event(stdout, "INFO", "Sphere radius resized to %.2f",
			sphere->radius);
		update_object(object);
	}
}
