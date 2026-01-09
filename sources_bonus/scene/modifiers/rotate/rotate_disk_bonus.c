/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_disk_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:23:39 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 11:22:15 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	rotate_disk(t_object *object, t_vec3 rotation_axis)
{
	t_real	angle;
	t_vec3	axis_input;
	t_mat4	rotation_matrix;
	t_disk	*disk;

	angle = vec3_len(rotation_axis);
	if (angle < EPSILON)
		return ;
	disk = &object->u_data.disk;
	axis_input = vec3_normalize(rotation_axis);
	rotation_matrix = matrix_axis_angle(axis_input, angle);
	apply_rotation_to_matrix(object, rotation_matrix);
	disk->normal.x = object->transform.m[0][1];
	disk->normal.y = object->transform.m[1][1];
	disk->normal.z = object->transform.m[2][1];
	disk->normal = vec3_normalize(disk->normal);
}
