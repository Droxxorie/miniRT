/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_rectangle_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:40:39 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 11:22:38 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	rotate_rectangle(t_object *object, t_vec3 rotation_axis)
{
	t_real		angle;
	t_vec3		axis_input;
	t_mat4		rotation_matrix;
	t_rectangle	*rectangle;

	angle = vec3_len(rotation_axis);
	if (angle < EPSILON)
		return ;
	rectangle = &object->u_data.rectangle;
	axis_input = vec3_normalize(rotation_axis);
	rotation_matrix = matrix_axis_angle(axis_input, angle);
	apply_rotation_to_matrix(object, rotation_matrix);
	rectangle->normal.x = object->transform.m[0][1];
	rectangle->normal.y = object->transform.m[1][1];
	rectangle->normal.z = object->transform.m[2][1];
	rectangle->normal = vec3_normalize(rectangle->normal);
}
