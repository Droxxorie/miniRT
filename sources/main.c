/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:07:55 by eraad             #+#    #+#             */
/*   Updated: 2025/12/10 22:28:00 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc < 2 || argc > 5)
		print_usage();
	scene = (t_scene *)ft_calloc(1, sizeof(t_scene));
	if (scene == NULL)
		sys_print_error_exit(ERR_SCENE_MEM);
	if (init_scene(scene, argv[1]) == EXIT_FAILURE)          // TODO
		print_error_free_exit(scene, ERR_SCENE_INIT); // TODO
	prepare_cameras(scene);                     // TODO
	if (init_buffer(scene) == FALSE)                  // TODO
		print_error_free_exit(scene, ERR_MLX_INIT);   // TODO
	if (ft_match(argv[2], SAVE_FLAG))                 // TODO
		scene->render_mode == SHADED;
	if (update(scene) == FALSE) // TODO
		print_error_free_exit(scene, ERR_SCENE_RENDER); // TODO
	if (scene->render_mode == SHADED)
		save_bmp(&scene->frame_buffer, "save.bmp"); // TODO
	hook_init(scene);                     // TODO
	return (0); //? ou return (1) jsp
}
