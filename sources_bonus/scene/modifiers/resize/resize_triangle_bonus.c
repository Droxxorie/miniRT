/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_triangle_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:48:22 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 20:01:36 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_triangle(t_object *object, int mode, int direction)
{
	t_mat4		scale_matrix;
	t_real		factor;

	(void)mode;
	if (direction > 0)
		factor = 1.1;
	else
		factor = 0.9;
	scale_matrix = make_scale_matrix((t_vec3){factor, factor, factor});
	object->transform = mat4_mult_mat4(object->transform, scale_matrix);
	set_transform(object, object->transform);
	log_event(stdout, "INFO", "Triangle resized");
}
