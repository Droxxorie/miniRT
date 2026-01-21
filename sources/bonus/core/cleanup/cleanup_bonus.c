/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:55:04 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 19:53:15 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	destroy_scene(t_scene *scene)
{
	if (!scene)
		return ;
	log_event(stderr, "INFO", "Cleaning up scene resources...\n");
	if (scene->mlx_window.mlx_ptr)
	{
		free_materials(scene->mlx_window.mlx_ptr, scene->materials);
		if (scene->frame_buffer.ptr)
			mlx_destroy_image(scene->mlx_window.mlx_ptr,
				scene->frame_buffer.ptr);
		if (scene->mlx_window.win_ptr)
			mlx_destroy_window(scene->mlx_window.mlx_ptr,
				scene->mlx_window.win_ptr);
		mlx_destroy_display(scene->mlx_window.mlx_ptr);
		free(scene->mlx_window.mlx_ptr);
	}
	else
		free_materials(NULL, scene->materials);
	destroy_bvh(scene);
	free_objects(scene->objects);
	free_lights(scene->lights);
	free_cameras(scene->cameras);
	free(scene->save_file);
	free(scene);
	log_event(stdout, "SUCCESS", "Scene destroyed successfully!\n");
}

t_status	clean_exit(t_scene *scene, t_status status)
{
	destroy_scene(scene);
	if (status == EXIT_SUCCESS)
		log_event(stdout, "SUCCESS", "Exited successfully!\n");
	else
		log_event(stdout, "ERROR", "Exited with errors!\n");
	exit(status);
	return (status);
}
