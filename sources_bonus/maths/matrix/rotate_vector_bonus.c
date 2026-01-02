/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_vector_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:31:32 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:40:32 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_vec3	rotate_vector(t_vec3 vector, t_vec3 axis, t_real angle)
{
	t_mat4	rotation_matrix;

	rotation_matrix = matrix_axis_angle(axis, angle);
	return (mat4_mult_vec3(rotation_matrix, vector));
}
