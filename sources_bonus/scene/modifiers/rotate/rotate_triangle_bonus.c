/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_triangle_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:40:44 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 22:47:16 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_vec3	rotate_point_around_center(t_point3 point, t_point3 center,
		t_mat4 rotation_matrix)
{
	t_vec3	temp;

	temp = vec3_sub(point, center);
	temp = mat4_mult_vec3(rotation_matrix, temp);
	return (vec3_add(temp, center));
}

void	rotate_triangle(t_object *object, t_vec3 rotation_axis)
{
	t_point3	center;
	t_real		angle;
	t_vec3		axis_input;
	t_mat4		rotation_matrix;
	t_triangle	*triangle;

	angle = vec3_len(rotation_axis);
	if (angle < EPSILON)
		return ;
	triangle = &object->u_data.triangle;
	center = vec3_scale(vec3_add(vec3_add(triangle->p1, triangle->p2),
				triangle->p3), 1.0 / 3.0);
	axis_input = vec3_normalize(rotation_axis);
	rotation_matrix = matrix_axis_angle(axis_input, angle);
	triangle->p1 = rotate_point_around_center(triangle->p1, center,
			rotation_matrix);
	triangle->p2 = rotate_point_around_center(triangle->p2, center,
			rotation_matrix);
	triangle->p3 = rotate_point_around_center(triangle->p3, center,
			rotation_matrix);
	update_object_matrix(object);
}
