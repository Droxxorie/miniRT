/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 20:17:19 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:44:25 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	init_default_values(t_scene *scene)
{
	scene->mlx_window.width = WINDOW_WIDTH;
	scene->mlx_window.height = WINDOW_HEIGHT;
	scene->mlx_window.aspect_ratio = (t_real)WINDOW_WIDTH
		/ (t_real)WINDOW_HEIGHT;
	scene->ambient.r = -1;
	scene->objects = NULL;
	scene->lights = NULL;
	scene->cameras = NULL;
	scene->active_camera = NULL;
	scene->selected_object = NULL;
	scene->selected_light = NULL;
	scene->control_mode = TRANSLATE;
	scene->shift_pressed = FALSE;
}

static t_status	validate_scene(t_scene *scene)
{
	if (scene->ambient.r < 0)
	{
		print_error(ERR_NO_AMB);
		return (EXIT_FAILURE);
	}
	if (scene->cameras == NULL)
	{
		print_error(ERR_NO_CAM);
		return (EXIT_FAILURE);
	}
	if (scene->mlx_window.height <= 0 || scene->mlx_window.width <= 0)
	{
		print_error(ERR_RES);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_status	load_scene(t_scene *scene, const char *file_path)
{
	log_detail("Loading scene from file: ", file_path);
	init_default_values(scene);
	if (parse_scene_file(scene, file_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (validate_scene(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	log_scene_stats(scene);
	return (EXIT_SUCCESS);
}
