/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_scene_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:52:51 by eraad             #+#    #+#             */
/*   Updated: 2026/01/15 17:38:26 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	reset_camera_state(t_camera *camera)
{
	camera->position = camera->initial_position;
	camera->direction = camera->initial_direction;
	camera->fov = camera->initial_fov;
	camera->tilt = camera->initial_tilt;
	update_camera(camera, camera->aspect_ratio);
}

void	reset_light_state(t_light *light)
{
	light->position = light->initial_position;
	light->brightness = light->initial_brightness;
	light->active = TRUE;
}

void	reset_object_state(t_object *object)
{
	t_torus	*torus;

	if (!object)
		return ;
	object->visible = TRUE;
	object->transform = object->initial_transform;
	set_transform(object, object->transform);
	if (object->type == TORUS)
	{
		torus = &object->u_data.torus;
		torus->major_radius = torus->initial_major_radius;
		torus->minor_radius = torus->initial_minor_radius;
		torus->major_radius_sq = torus->major_radius * torus->major_radius;
		torus->minor_radius_sq = torus->minor_radius * torus->minor_radius;
		torus->diff_radius_sq = torus->major_radius_sq - torus->minor_radius_sq;
	}
}

static void	reset_bvh_state(t_bvh_node *node)
{
	t_bvh_node	*current_node;

	current_node = node;
	while (current_node)
	{
		reset_object_state(current_node->content);
		current_node = current_node->left_child;
	}
	current_node = node->right_child;
	while (current_node)
	{
		reset_object_state(current_node->content);
		current_node = current_node->right_child;
	}
}

void	reset_scene_state(t_scene *scene)
{
	t_light		*current_light;
	t_camera	*current_camera;

	current_light = scene->lights;
	current_camera = scene->cameras;
	reset_bvh_state(scene->bvh_root);
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
