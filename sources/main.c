/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:07:55 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 17:40:49 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc < 2 || argc > 3)
		print_usage();
	scene = ft_calloc(1, sizeof(t_scene));
	if (scene == NULL)
		sys_print_error_exit(ERR_SCENE_MEM);
	if (load_scene(scene, argv[1]) == EXIT_FAILURE)
		print_error_free_exit(scene, ERR_SCENE_INIT);
	if (argc == 3 && ft_strcmp(argv[2], SAVE_FLAG) == 0)
		scene->render_mode = SHADED;
	prepare_cameras(scene);
	if (init_graphics(scene) == EXIT_FAILURE)
		print_error_free_exit(scene, ERR_INIT_GRAPHICS);
	if (update(scene) == FALSE)                         // TODO
		print_error_free_exit(scene, ERR_SCENE_RENDER); // TODO
	if (scene->render_mode == SHADED)
	{
		save_bmp(&scene->frame_buffer, "save.bmp"); // TODO On vera si on garde
		clean_exit(scene, EXIT_SUCCESS);
	}
	hook_init(scene);                               // TODO
	mlx_loop(scene->mlx_window.mlx_ptr);                  // TODO
	return (EXIT_SUCCESS);
}
