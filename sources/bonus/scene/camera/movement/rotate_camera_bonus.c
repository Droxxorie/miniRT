/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 08:27:57 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 17:30:16 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	yaw(t_camera *camera, t_real angle)
{
	t_mat4	rot_y;

	if (fabsf(angle) < EPSILON)
		return ;
	rot_y = rotation_mat_y(angle);
	camera->direction = mat4_mult_vec3(rot_y, camera->direction);
	camera->direction = vec3_normalize(camera->direction);
}

static void	pitch(t_camera *camera, t_real angle)
{
	t_vec3	right;
	t_vec3	world_up;
	t_vec3	new_direction;
	t_mat4	rot_axis;

	if (fabsf(angle) < EPSILON)
		return ;
	world_up = (t_vec3){0.0, 1.0, 0.0};
	right = vec3_cross(camera->direction, world_up);
	if (vec3_len_squared(right) < EPSILON)
		right = (t_vec3){1.0, 0.0, 0.0};
	else
		right = vec3_normalize(right);
	rot_axis = matrix_axis_angle(right, angle);
	new_direction = mat4_mult_vec3(rot_axis, camera->direction);
	new_direction = vec3_normalize(new_direction);
	if (fabsf(new_direction.y) < 0.9)
		camera->direction = new_direction;
}

static void	tilt(t_camera *camera, t_real angle)
{
	if (fabsf(angle) > EPSILON)
	{
		camera->tilt += angle;
		if (camera->tilt > PI)
			camera->tilt -= TWO_PI;
		else if (camera->tilt < -PI)
			camera->tilt += TWO_PI;
	}
}

void	rotate_camera(t_camera *camera, t_vec3 input_scaled,
		t_real aspect_ratio)
{
	t_real	speed;
	t_vec3	adjusted_input;

	speed = ROT_SPEED * camera->scale_factor;
	adjusted_input = vec3_scale(input_scaled, speed);
	yaw(camera, adjusted_input.z);
	pitch(camera, adjusted_input.x);
	tilt(camera, adjusted_input.y);
	update_camera(camera, aspect_ratio);
}
