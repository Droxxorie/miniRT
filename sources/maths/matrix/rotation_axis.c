/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_axis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:34:43 by eraad             #+#    #+#             */
/*   Updated: 2025/12/20 19:04:27 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_mat4	matrix_axis_angle(t_vec3 axis, t_real angle)
{
	t_mat4	result;
	t_real	cos_theta;
	t_real	sin_theta;
	t_real	t;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	t = 1 - cos_theta;
	result = identity_matrix();
	result.m[0][0] = t * axis.x * axis.x + cos_theta;
	result.m[0][1] = t * axis.x * axis.y - sin_theta * axis.z;
	result.m[0][2] = t * axis.x * axis.z + sin_theta * axis.y;
	result.m[1][0] = t * axis.y * axis.x + sin_theta * axis.z;
	result.m[1][1] = t * axis.y * axis.y + cos_theta;
	result.m[1][2] = t * axis.y * axis.z - sin_theta * axis.x;
	result.m[2][0] = t * axis.z * axis.x - sin_theta * axis.y;
	result.m[2][1] = t * axis.z * axis.y + sin_theta * axis.x;
	result.m[2][2] = t * axis.z * axis.z + cos_theta;
	return (result);
}
