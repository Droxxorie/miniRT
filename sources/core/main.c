/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:07:55 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 20:16:26 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc != 2)
		print_usage();
	scene = ft_calloc(1, sizeof(t_scene));
	if (scene == NULL)
		sys_print_error_exit(ERR_MEM_SCENE);
	if (load_scene(scene, argv[1]) == EXIT_FAILURE)
		print_error_free_exit(scene, ERR_INIT_SCENE);
	prepare_cameras(scene);
	if (init_graphics(scene) == EXIT_FAILURE)
		print_error_free_exit(scene, ERR_INIT_GRAPHICS);
	if (render_frame(scene) == EXIT_FAILURE)
		print_error_free_exit(scene, ERR_RENDER);
	input_manager(scene);
	mlx_loop(scene->mlx_window.mlx_ptr);
	return (EXIT_SUCCESS);
}
