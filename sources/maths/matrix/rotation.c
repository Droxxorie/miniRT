/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:49:53 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 12:34:00 by eraad            ###   ########.fr       */
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

// t_mat4	make_rotation_matrix(t_vec3 angles)
// {
// 	t_mat4	rot_x;
// 	t_mat4	rot_y;
// 	t_mat4	rot_z;
// 	t_mat4	mat;

// 	rot_x = rotation_mat_x(angles.x);
// 	rot_y = rotation_mat_y(angles.y);
// 	rot_z = rotation_mat_z(angles.z);
// 	mat = identity_matrix();
// 	mat = mat4_mult_mat4(rot_y, rot_x);
// 	mat = mat4_mult_mat4(rot_z, mat);
// 	return (mat);
// }

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

t_mat4	rotation_align(t_vec3	dest)
{
	t_vec3	axis;
	t_real	angle;
	t_vec3	default_dir;

	default_dir = (t_vec3){0.0, 1.0, 0.0};
	if (fabs(dest.x) < EPSILON && fabs(dest.z) < EPSILON && dest.y > 0)
		return (identity_matrix());
	if (fabs(dest.x) < EPSILON && fabs(dest.z) < EPSILON && dest.y < 0)
		return (rotation_mat_x(PI));
	axis = vec3_cross(default_dir, dest);
	axis = vec3_normalize(axis);
	angle = acos(vec3_dot(default_dir, dest));
	return (matrix_axis_angle(axis, angle));
}

t_mat4	make_scale_matrix(t_vec3 scale)
{
	t_mat4	mat;

	mat = identity_matrix();
	mat.m[0][0] = scale.x;
	mat.m[1][1] = scale.y;
	mat.m[2][2] = scale.z;
	return (mat);
}
