/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:07:55 by eraad             #+#    #+#             */
/*   Updated: 2025/12/21 18:59:43 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	print_controls(void)
{
	ft_putstr_fd(B_YELLOW"", 1);
	ft_putstr_fd("\n╔══════════════════════════════════════════════════╗\n", 1);
	ft_putstr_fd("║                 miniRT CONTROLS                  ║\n", 1);
	ft_putstr_fd("╚══════════════════════════════════════════════════╝\n", 1);
	ft_putstr_fd("╔══════════════════════════════════════════════════╗\n", 1);
	ft_putstr_fd("║                                     - GENERAL -  ║\n", 1);
	ft_putstr_fd("║  [ESC]   Exit the program                        ║\n", 1);
	ft_putstr_fd("║  [TAB]   Switch between ROT & TRANS mode         ║\n", 1);
	ft_putstr_fd("║                                                  ║\n", 1);
	ft_putstr_fd("║                                   - SELECTION -  ║\n", 1);
	ft_putstr_fd("║  [L / R Click]   Select Object / Camera          ║\n", 1);
	ft_putstr_fd("║  [L]             Select light source             ║\n", 1);
	ft_putstr_fd("║                                                  ║\n", 1);
	ft_putstr_fd("║                                    - MOVEMENT -  ║\n", 1);
	ft_putstr_fd("║  [W / S]   Move Forward / Backward               ║\n", 1);
	ft_putstr_fd("║  [A / D]   Move Left / Right                     ║\n", 1);
	ft_putstr_fd("║  [Q / E]   Move Down / Up                        ║\n", 1);
	ft_putstr_fd("║                                                  ║\n", 1);
	ft_putstr_fd("║                                - MODIFICATION -  ║\n", 1);
	ft_putstr_fd("║  [+ / -]             Resize Diameter             ║\n", 1);
	ft_putstr_fd("║  [SHIFT] + [+ / -]   Resize Height (Cylinder)    ║\n", 1);
	ft_putstr_fd("╚══════════════════════════════════════════════════╝\n", 1);
	ft_putstr_fd(RESET "\n", 1);
}

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
	log_info("Starting render loop...");
	print_controls();
	if (render_frame(scene) == EXIT_FAILURE)
		print_error_free_exit(scene, ERR_RENDER);
	input_manager(scene);
	mlx_loop(scene->mlx_window.mlx_ptr);
	return (EXIT_SUCCESS);
}
