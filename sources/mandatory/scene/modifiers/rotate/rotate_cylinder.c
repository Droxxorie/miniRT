/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:16:34 by eraad             #+#    #+#             */
/*   Updated: 2025/12/20 19:10:31 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	rotate_cylinder(t_object *object, t_vec3 rotation_axis)
{
	t_real		angle;
	t_vec3		axis_input;
	t_mat4		rotation_matrix;
	t_cylinder	*cylinder;

	angle = vec3_len(rotation_axis);
	if (angle < EPSILON)
		return ;
	cylinder = &object->u_data.cylinder;
	axis_input = vec3_normalize(rotation_axis);
	rotation_matrix = matrix_axis_angle(axis_input, angle);
	apply_rotation_to_matrix(object, rotation_matrix);
	cylinder->axis.x = object->transform.m[0][1];
	cylinder->axis.y = object->transform.m[1][1];
	cylinder->axis.z = object->transform.m[2][1];
	cylinder->axis = vec3_normalize(cylinder->axis);
}
