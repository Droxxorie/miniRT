/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:38:32 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 17:35:16 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void init_default_values(t_scene *scene)
{
	scene->mlx_window.width = WINDOW_WIDTH;
	scene->mlx_window.height = WINDOW_HEIGHT;
	scene->mlx_window.aspect_ratio = (t_real)WINDOW_WIDTH / (t_real)WINDOW_HEIGHT;
	scene->ambient.r = -1;
	scene->objects = NULL;
	scene->lights = NULL;
	scene->cameras = NULL;
}

static t_status	validate_scene(t_scene *scene)
{
	if (scene->cameras == NULL)
	{
		print_error(ERR_INIT_NO_CAM);
		return (EXIT_FAILURE);
	}
	if (scene->ambient.r < 0)
	{
		print_error(ERR_INIT_NO_AMB);
		return (EXIT_FAILURE);
	}
	if (scene->mlx_window.height <= 0 || scene->mlx_window.width <= 0)
	{
		print_error(ERR_INIT_RES);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_status	load_scene(t_scene *scene, char *file_path)
{
	// log_info("Initializing scene"); // ? debug a voir si je laisse
	init_default_values(scene);
	if (parse_scene_file(scene, file_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (validate_scene(scene) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
