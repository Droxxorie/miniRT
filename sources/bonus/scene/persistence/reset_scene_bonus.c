/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_scene_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:52:51 by eraad             #+#    #+#             */
/*   Updated: 2026/01/22 20:16:25 by eraad            ###   ########.fr       */
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
	light->direction = light->initial_direction;
	light->cos_theta = light->initial_cos_theta;
	light->u = light->initial_u;
	light->v = light->initial_v;
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
	compute_object_bounds(object);
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

static void	reset_bvh_objects(t_bvh_node *node)
{
	t_object	*current;

	if (!node)
		return ;
	if (node->left_child || node->right_child)
	{
		reset_bvh_objects(node->left_child);
		reset_bvh_objects(node->right_child);
	}
	else
	{
		current = node->content;
		while (current)
		{
			reset_object_state(current);
			current = current->next;
		}
	}
}

void	reset_scene_state(t_scene *scene)
{
	t_light		*current_light;
	t_camera	*current_camera;

	current_light = scene->lights;
	current_camera = scene->cameras;
	reset_bvh_objects(scene->bvh_root);
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
	scene->selected_object = NULL;
	scene->selected_light = NULL;
}
