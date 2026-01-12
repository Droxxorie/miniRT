/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:07:55 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 12:54:08 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_scene	*init_scene_struct(int argc, char **argv)
{
	t_scene	*scene;

	if (argc < 2 || argc > 4)
		return (print_usage(), NULL);
	log_event(stdout, "INFO", "Initializing miniRT Engine (Bonus Edition)\n");
	log_event(stdout, "INFO", "Detected %li logical CPU cores\n",
		sysconf(_SC_NPROCESSORS_ONLN));
	scene = ft_calloc(1, sizeof(t_scene));
	if (scene == NULL)
		sys_print_error_exit(ERR_MEM_SCENE);
	if (argc == 3 || argc == 4)
		setup_save_mode(argc, argv, scene);
	if (scene->to_save)
	{
		log_event(stdout, "WARN", "Save mode activated\n");
		log_event(stdout, "INFO", "Save file: %s%s%s\n", UNDERLINE,
			scene->save_file, RESET);
	}
	else
		log_event(stdout, "INFO", "Interactive mode activated\n");
	return (scene);
}

static void	load_scene_data(t_scene *scene, char *filename)
{
	if (load_scene(scene, filename) == EXIT_FAILURE)
		clean_exit(scene, EXIT_FAILURE);
	prepare_cameras(scene);
	save_scene_state(scene);
}

static void	execute_minirt(t_scene *scene)
{
	if (init_graphics(scene) == EXIT_FAILURE)
		print_error_free_exit(scene, ERR_GRAPHICS);
	log_event(stdout, "INFO", "Graphics window size: %s%dx%d%s\n", UNDERLINE,
		scene->mlx_window.width, scene->mlx_window.height, RESET);
	log_event(stdout, "INFO", "Starting multi-threaded rendering\n");
	log_event(stdout, "INFO", "Threads: %li\n", sysconf(_SC_NPROCESSORS_ONLN));
	build_bvh(scene);
	render_frame(scene);
	if (scene->to_save == TRUE)
	{
		mkdir("saved", 0755);
		save_image_to_bmp(scene);
		clean_exit(scene, EXIT_SUCCESS);
	}
	else
		print_controls();
	input_manager(scene);
	mlx_loop(scene->mlx_window.mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	entry_message();
	scene = init_scene_struct(argc, argv);
	if (scene == NULL)
		return (EXIT_FAILURE);
	load_scene_data(scene, argv[1]);
	execute_minirt(scene);
	return (EXIT_SUCCESS);
}
