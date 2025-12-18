/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:07:55 by eraad             #+#    #+#             */
/*   Updated: 2025/12/18 16:36:37 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc != 2)
		print_usage();
	log_info("Initializing miniRT...");
	scene = ft_calloc(1, sizeof(t_scene));
	if (scene == NULL)
		sys_print_error_exit(ERR_MEM_SCENE);
	if (load_scene(scene, argv[1]) == EXIT_FAILURE)
		clean_exit(scene, EXIT_FAILURE);
	log_info("Preparing cameras...");
	prepare_cameras(scene);
	log_info("Initializing graphics...");
	if (init_graphics(scene) == EXIT_FAILURE)
		print_error_free_exit(scene, ERR_GRAPHICS);
	log_info("Starting render loop...\n");
	if (render_frame(scene) == EXIT_FAILURE)
		print_error_free_exit(scene, ERR_RENDER);
	input_manager(scene);
	mlx_loop(scene->mlx_window.mlx_ptr);
	return (EXIT_SUCCESS);
}
