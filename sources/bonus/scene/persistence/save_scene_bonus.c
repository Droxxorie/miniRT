/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_scene_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:31:15 by eraad             #+#    #+#             */
/*   Updated: 2026/01/22 19:08:51 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	save_objects_state(t_object *objects)
{
	t_object	*current;
	t_torus		*torus;

	current = objects;
	while (current)
	{
		current->initial_transform = current->transform;
		if (current->type == TORUS)
		{
			torus = &current->u_data.torus;
			torus->initial_major_radius = torus->major_radius;
			torus->initial_minor_radius = torus->minor_radius;
		}
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
		current->initial_tilt = current->tilt;
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
		current->initial_direction = current->direction;
		current->initial_cos_theta = current->cos_theta;
		current->initial_u = current->u;
		current->initial_v = current->v;
		current = current->next;
	}
}

void	save_scene_state(t_scene *scene)
{
	log_event(stdout, "INFO", "Saving initial scene state...\n");
	save_objects_state(scene->objects);
	save_cameras_state(scene->cameras);
	save_lights_state(scene->lights);
}
