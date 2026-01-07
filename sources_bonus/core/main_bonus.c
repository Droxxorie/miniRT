/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:07:55 by eraad             #+#    #+#             */
/*   Updated: 2026/01/07 00:33:36 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_scene	*init_scene_struct(int argc, char **argv)
{
	t_scene	*scene;

	if (argc < 2 || argc > 4)
		return (print_usage(), NULL);
	log_info("Initializing miniRT...");
	scene = ft_calloc(1, sizeof(t_scene));
	if (scene == NULL)
		sys_print_error_exit(ERR_MEM_SCENE);
	if (argc == 3 || argc == 4)
		setup_save_mode(argc, argv, scene);
	return (scene);
}

static void	load_scene_data(t_scene *scene, char *filename)
{
	if (load_scene(scene, filename) == EXIT_FAILURE)
		clean_exit(scene, EXIT_FAILURE);
	prepare_cameras(scene);
}

static void	execute_minirt(t_scene *scene)
{
	if (init_graphics(scene) == EXIT_FAILURE)
		print_error_free_exit(scene, ERR_GRAPHICS);
	log_info("Starting rendering...");
	
	render_frame(scene);
	if (scene->to_save == FALSE)
		print_controls();
	if (scene->to_save == TRUE)
	{
		save_image_to_bmp(scene);
		clean_exit(scene, EXIT_SUCCESS);
	}
	input_manager(scene);
	mlx_loop(scene->mlx_window.mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	scene = init_scene_struct(argc, argv);
	load_scene_data(scene, argv[1]);
	execute_minirt(scene);
	return (EXIT_SUCCESS);
}
