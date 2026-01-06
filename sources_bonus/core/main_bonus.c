/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:07:55 by eraad             #+#    #+#             */
/*   Updated: 2026/01/06 17:45:39 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc < 2 || argc > 4)
		return (print_usage(), EXIT_FAILURE);
	log_info("Initializing miniRT...");
	scene = ft_calloc(1, sizeof(t_scene));
	if (scene == NULL)
		sys_print_error_exit(ERR_MEM_SCENE);
	if (argc == 3 || argc == 4)
		setup_save_mode(argc, argv, scene);
	if (load_scene(scene, argv[1]) == EXIT_FAILURE)
		clean_exit(scene, EXIT_FAILURE);
	prepare_cameras(scene);
	if (init_graphics(scene) == EXIT_FAILURE)
		print_error_free_exit(scene, ERR_GRAPHICS);
	log_info("Starting render loop...");
	print_controls();
	render_frame(scene);
	input_manager(scene);
	mlx_loop(scene->mlx_window.mlx_ptr);
	return (EXIT_SUCCESS);
}
