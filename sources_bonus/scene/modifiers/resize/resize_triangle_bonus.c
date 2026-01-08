/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_triangle_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:48:22 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 23:48:05 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_triangle(t_object *object, int mode, int direction)
{
	t_triangle	*triangle;
	t_point3	center;
	t_real		scale_factor;

	(void)mode;
	triangle = &object->u_data.triangle;
	scale_factor = 1.0 + (direction * STEP_SIZE);
	center = vec3_scale(vec3_add(vec3_add(triangle->p1, triangle->p2),
				triangle->p3), 1.0 / 3.0);
	triangle->p1 = vec3_add(center, vec3_scale(vec3_sub(triangle->p1, center),
				scale_factor));
	triangle->p2 = vec3_add(center, vec3_scale(vec3_sub(triangle->p2, center),
				scale_factor));
	triangle->p3 = vec3_add(center, vec3_scale(vec3_sub(triangle->p3, center),
				scale_factor));
	log_event(stdout, "INFO", "Triangle resized by a factor of %.2f",
		scale_factor);
	update_object_matrix(object);
}
