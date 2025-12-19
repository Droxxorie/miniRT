/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:31:32 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 19:31:34 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3	rotate_vector(t_vec3 vector, t_vec3 axis, t_real angle)
{
	t_mat4 rotation_matrix;

	rotation_matrix = matrix_axis_angle(axis, angle);
	return (mat4_mult_vec3(rotation_matrix, vector));
}
