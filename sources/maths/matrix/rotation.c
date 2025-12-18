/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:49:53 by eraad             #+#    #+#             */
/*   Updated: 2025/12/18 21:50:07 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_mat4	rotation_mat_x(t_real theta)
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

static t_mat4	rotation_mat_y(t_real theta)
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

static t_mat4	rotation_mat_z(t_real theta)
{
	t_mat4	mat;
	t_real	cos_theta;
	t_real	sin_theta;

	cos_theta = cos(theta);
	sin_theta = sin(theta);
	mat = identity_matrix();
	mat.m[0][0] = cos_theta;
	mat.m[0][1] = -sin_theta;
	mat.m[1][0] = sin_theta;
	mat.m[1][1] = cos_theta;
	return (mat);
}

t_mat4	make_rotation_matrix(t_vec3 angles)
{
	t_mat4	rot_x;
	t_mat4	rot_y;
	t_mat4	rot_z;
	t_mat4	mat;

	rot_x = rotation_mat_x(angles.x);
	rot_y = rotation_mat_y(angles.y);
	rot_z = rotation_mat_z(angles.z);
	mat = identity_matrix();
	mat = mat4_mult_mat4(rot_y, rot_x);
	mat = mat4_mult_mat4(rot_z, mat);
	return (mat);
}
