/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:38:32 by eraad             #+#    #+#             */
/*   Updated: 2025/12/10 18:31:10 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_bool	init_scene(t_scene *scene, char *file_path)
{
	log_info("Initializing scene");
	scene->mlx_window.ptr = mlx_init();
	scene->mlx_window.width = WINDOW_WIDTH;
	scene->mlx_window.height = WINDOW_HEIGHT;
	scene->mlx_window.aspect_ratio = ASPECT_RATIO;
	scene->render_mode = FLAT;
	scene->ambient = -1;
	// scene->camera_id = 1;
	scene->camera_count = 0;
	if (!parse_to_scene(scene, file_path)) // TODO
		return (FALSE);
	return (verify_scene(scene)); // TODO
}
