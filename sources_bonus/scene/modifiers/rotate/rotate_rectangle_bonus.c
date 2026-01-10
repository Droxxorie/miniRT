/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_rectangle_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:40:39 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 20:01:55 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	rotate_rectangle(t_object *object, t_vec3 rotation_axis)
{
	t_real		angle;
	t_vec3		axis_input;
	t_mat4		rotation_matrix;

	angle = vec3_len(rotation_axis);
	if (angle < EPSILON)
		return ;
	axis_input = vec3_normalize(rotation_axis);
	rotation_matrix = matrix_axis_angle(axis_input, angle);
	apply_rotation_to_matrix(object, rotation_matrix);
}
