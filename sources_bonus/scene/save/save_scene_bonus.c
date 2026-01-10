/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_scene_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:31:15 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 20:42:22 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	save_objects_state(t_object *objects)
{
	t_object	*current;

	current = objects;
	while (current)
	{
		if (current->type == SPHERE)
			save_sphere_state(&current->u_data.sphere);
		else if (current->type == PLANE)
			save_plane_state(&current->u_data.plane);
		else if (current->type == CYLINDER)
			save_cylinder_state(&current->u_data.cylinder);
		else if (current->type == RECTANGLE)
			save_rectangle_state(&current->u_data.rectangle);
		else if (current->type == DISK)
			save_disk_state(&current->u_data.disk);
		else if (current->type == TRIANGLE)
			save_triangle_state(&current->u_data.triangle);
		else if (current->type == TORUS)
			save_torus_state(&current->u_data.torus);
		current = current->next;
	}
}

static void	save_cameras_state(t_camera *cameras)
{
	t_camera	*current;

	current = cameras;
	while (current)
	{
		current->initial_position = current->position;
		current->initial_direction = current->direction;
		current->initial_fov = current->fov;
		current = current->next;
	}
}

static void	save_lights_state(t_light *lights)
{
	t_light	*current;

	current = lights;
	while (current)
	{
		current->initial_position = current->position;
		current->initial_brightness = current->brightness;
		current = current->next;
	}
}

void	save_scene_state(t_scene *scene)
{
	log_event(stdout, "INFO", "Saving initial scene state...");
	save_objects_state(scene->objects);
	save_cameras_state(scene->cameras);
	save_lights_state(scene->lights);
}
