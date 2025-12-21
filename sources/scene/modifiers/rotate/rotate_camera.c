/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 08:27:57 by eraad             #+#    #+#             */
/*   Updated: 2025/12/21 19:01:40 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	yaw(t_camera *camera, t_real z)
{
	t_mat4	rot_y;

	if (fabs(z) > EPSILON)
	{
		rot_y = rotation_mat_y(z);
		camera->direction = mat4_mult_vec3(rot_y, camera->direction);
	}
}

static void	pitch(t_camera *camera, t_real x)
{
	t_vec3	camera_right;
	t_mat4	rot_x;

	if (fabs(x) > EPSILON)
	{
		camera_right = (t_vec3){camera->camera_to_world.m[0][0],
			camera->camera_to_world.m[1][0], camera->camera_to_world.m[2][0]};
		rot_x = matrix_axis_angle(camera_right, x);
		camera->direction = mat4_mult_vec3(rot_x, camera->direction);
	}
}

static void	tilt(t_camera *camera, t_real y)
{
	if (fabs(y) > EPSILON)
	{
		camera->tilt += y;
		if (camera->tilt > PI)
			camera->tilt -= TWO_PI;
		else if (camera->tilt < -PI)
			camera->tilt += TWO_PI;
	}
}

void	rotate_camera(t_camera *camera, t_vec3 input_scaled,
		t_real aspect_ratio)
{
	yaw(camera, input_scaled.z);
	pitch(camera, input_scaled.x);
	tilt(camera, input_scaled.y);
	camera->direction = vec3_normalize(camera->direction);
	update_camera_matrix(camera, aspect_ratio);
}
