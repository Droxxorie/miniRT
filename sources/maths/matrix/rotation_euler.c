/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_euler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:33:32 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 19:33:46 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_mat4	rotation_mat_x(t_real theta)
{
	t_mat4	mat;
	t_real	cos_theta;
	t_real	sin_theta;

	cos_theta = cos(theta);
	sin_theta = sin(theta);
	mat = identity_matrix();
	mat.m[1][1] = cos_theta;
	mat.m[1][2] = -sin_theta;
	mat.m[2][1] = sin_theta;
	mat.m[2][2] = cos_theta;
	return (mat);
}

t_mat4	rotation_mat_y(t_real theta)
{
	t_mat4	mat;
	t_real	cos_theta;
	t_real	sin_theta;

	cos_theta = cos(theta);
	sin_theta = sin(theta);
	mat = identity_matrix();
	mat.m[0][0] = cos_theta;
	mat.m[0][2] = sin_theta;
	mat.m[2][0] = -sin_theta;
	mat.m[2][2] = cos_theta;
	return (mat);
}

t_mat4	rotation_mat_z(t_real theta)
{
	t_mat4 mat;
	t_real cos_theta;
	t_real sin_theta;

	cos_theta = cos(theta);
	sin_theta = sin(theta);
	mat = identity_matrix();
	mat.m[0][0] = cos_theta;
	mat.m[0][1] = -sin_theta;
	mat.m[1][0] = sin_theta;
	mat.m[1][1] = cos_theta;
	return (mat);
}
