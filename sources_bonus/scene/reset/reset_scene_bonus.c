/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_scene_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:52:51 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 23:45:49 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	reset_camera_state(t_camera *camera)
{
	camera->position = camera->initial_position;
	camera->direction = camera->initial_direction;
	camera->fov = camera->initial_fov;
	update_camera_matrix(camera, camera->aspect_ratio);
}

void	reset_light_state(t_light *light)
{
	light->position = light->initial_position;
	light->brightness = light->initial_brightness;
	light->active = TRUE;
}

void	reset_object_state(t_object *object)
{
	object->visible = TRUE;
	if (object->type == SPHERE)
		reset_sphere_state(object);
	else if (object->type == PLANE)
		reset_plane_state(object);
	else if (object->type == CYLINDER)
		reset_cylinder_state(object);
	else if (object->type == RECTANGLE)
		reset_rectangle_state(object);
	else if (object->type == DISK)
		reset_disk_state(object);
	else if (object->type == TRIANGLE)
		reset_triangle_state(object);
}

void	reset_scene_state(t_scene *scene)
{
	t_object	*current_object;
	t_light		*current_light;
	t_camera	*current_camera;

	current_object = scene->objects;
	current_light = scene->lights;
	current_camera = scene->cameras;
	while (current_object)
	{
		reset_object_state(current_object);
		current_object = current_object->next;
	}
	while (current_light)
	{
		reset_light_state(current_light);
		current_light = current_light->next;
	}
	while (current_camera)
	{
		reset_camera_state(current_camera);
		current_camera = current_camera->next;
	}
	scene->active_camera = scene->cameras;
}
