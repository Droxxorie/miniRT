/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:59:19 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 12:15:03 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	rotate_object(t_object *object, t_vec3 rotation_axis, t_real angle)
{
	t_mat4	rotation_matrix;
	t_vec3	*axis_to_rotate;

	if (object->type == PLANE)
		axis_to_rotate = &object->u_data.plane.normal;
	else if (object->type == CYLINDER)
		axis_to_rotate = &object->u_data.cylinder.axis;
	else
		return ;
	rotation_matrix = matrix_axis_angle(rotation_axis, angle);
	*axis_to_rotate = mat4_mult_vec3(rotation_matrix, *axis_to_rotate);
	*axis_to_rotate = vec3_normalize(*axis_to_rotate);
	update_object_matrix(object);
}
