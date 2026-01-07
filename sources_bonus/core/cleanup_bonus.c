/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:55:04 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 00:25:51 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	free_objects(t_object *object)
{
	t_object	*temp;

	while (object)
	{
		temp = object->next;
		free(object);
		object = temp;
	}
}

static void	free_lights(t_light *light)
{
	t_light	*temp;

	while (light)
	{
		temp = light->next;
		free(light);
		light = temp;
	}
}

static void	free_cameras(t_camera *camera)
{
	t_camera	*temp;

	while (camera)
	{
		temp = camera->next;
		free(camera);
		camera = temp;
	}
}

void	destroy_scene(t_scene *scene)
{
	if (!scene)
		return ;
	log_event("INFO", "Cleaning up scene resources...");
	if (scene->mlx_window.mlx_ptr)
	{
		if (scene->frame_buffer.ptr)
			mlx_destroy_image(scene->mlx_window.mlx_ptr,
				scene->frame_buffer.ptr);
		if (scene->mlx_window.win_ptr)
			mlx_destroy_window(scene->mlx_window.mlx_ptr,
				scene->mlx_window.win_ptr);
		mlx_destroy_display(scene->mlx_window.mlx_ptr);
		free(scene->mlx_window.mlx_ptr);
	}
	free_objects(scene->objects);
	free_lights(scene->lights);
	free_cameras(scene->cameras);
	free(scene->save_file);
	free(scene);
	log_event("SUCCESS", "Scene destroyed successfully!");
}

t_status	clean_exit(t_scene *scene, t_status status)
{
	destroy_scene(scene);
	if (status == EXIT_SUCCESS)
		log_event("SUCCESS", "Exited successfully!");
	else
		log_event("ERROR", "Exited with errors!");
	exit(status);
	return (status);
}
