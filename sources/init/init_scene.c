/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:38:32 by eraad             #+#    #+#             */
/*   Updated: 2025/12/10 22:28:17 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_status	init_scene(t_scene *scene, char *file_path)
{
	log_info("Initializing scene");
	scene->mlx_window.ptr = mlx_init();
	scene->mlx_window.width = WINDOW_WIDTH;
	scene->mlx_window.height = WINDOW_HEIGHT;
	scene->mlx_window.aspect_ratio = ASPECT_RATIO;
	scene->render_mode = FLAT;
	scene->ambient = -1;
	scene->camera_count = 0;
	if (parse_scene_file(scene, file_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (verify_scene(scene)); // TODO
}
