/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:13:06 by eraad             #+#    #+#             */
/*   Updated: 2026/01/06 16:54:01 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	make_camera_to_world_matrix(t_camera *camera, t_vec3 up,
		t_vec3 right, t_vec3 forward)
{
	t_mat4	roll_matrix;

	camera->camera_to_world = identity_matrix();
	camera->camera_to_world.m[0][1] = up.x;
	camera->camera_to_world.m[1][1] = up.y;
	camera->camera_to_world.m[2][1] = up.z;
	camera->camera_to_world.m[0][0] = right.x;
	camera->camera_to_world.m[1][0] = right.y;
	camera->camera_to_world.m[2][0] = right.z;
	camera->camera_to_world.m[0][2] = -forward.x;
	camera->camera_to_world.m[1][2] = -forward.y;
	camera->camera_to_world.m[2][2] = -forward.z;
	camera->camera_to_world.m[0][3] = camera->position.x;
	camera->camera_to_world.m[1][3] = camera->position.y;
	camera->camera_to_world.m[2][3] = camera->position.z;
	if (fabs(camera->tilt) > EPSILON)
	{
		roll_matrix = rotation_mat_z(camera->tilt);
		camera->camera_to_world = mat4_mult_mat4(camera->camera_to_world,
				roll_matrix);
	}
}

void	update_camera_matrix(t_camera *camera, t_real aspect_ratio)
{
	t_vec3	up;
	t_vec3	right;
	t_vec3	forward;
	t_vec3	world_up;

	camera->aspect_ratio = aspect_ratio;
	camera->scale_factor = tan((camera->fov * (PI / 180.0)) * 0.5);
	forward = vec3_normalize(camera->direction);
	world_up = (t_vec3){0.0, 1.0, 0.0};
	if (fabs(forward.y) > 1 - EPSILON)
		right = (t_vec3){1.0, 0.0, 0.0};
	else
		right = vec3_normalize(vec3_cross(forward, world_up));
	up = vec3_cross(right, forward);
	up = vec3_normalize(up);
	make_camera_to_world_matrix(camera, up, right, forward);
}

void	prepare_cameras(t_scene *scene)
{
	t_camera	*current;
	int			count;

	log_info("Preparing cameras...");
	if (scene == NULL || scene->cameras == NULL)
		return ;
	current = scene->cameras;
	count = 0;
	while (current)
	{
		current->width = scene->mlx_window.width;
		current->height = scene->mlx_window.height;
		current->aspect_ratio = (t_real)current->width
			/ (t_real)current->height;
		update_camera_matrix(current, scene->mlx_window.aspect_ratio);
		current->id = ++count;
		current = current->next;
	}
	scene->active_camera = scene->cameras;
}
