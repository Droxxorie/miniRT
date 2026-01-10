/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_plane_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:06:18 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 21:30:23 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	rotate_plane(t_object *object, t_vec3 rotation_axis)
{
	t_real	angle;
	t_vec3	axis_input;
	t_mat4	rotation_matrix;
	t_plane	*plane;

	angle = vec3_len(rotation_axis);
	if (angle < EPSILON)
		return ;
	plane = &object->u_data.plane;
	axis_input = vec3_normalize(rotation_axis);
	rotation_matrix = matrix_axis_angle(axis_input, angle);
	apply_rotation_to_matrix(object, rotation_matrix);
	plane->normal.x = object->transform.m[0][1];
	plane->normal.y = object->transform.m[1][1];
	plane->normal.z = object->transform.m[2][1];
	plane->normal = vec3_normalize(plane->normal);
}
