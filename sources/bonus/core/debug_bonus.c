/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:31:04 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 18:42:26 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	setup_debug_mode(int argc, char **argv, t_scene *scene)
{
	scene->render_mode = RENDER_IMAGE;
	if (argc != 4)
	{
		print_error(ERR_DEBUG);
		print_usage();
		clean_exit(scene, EXIT_FAILURE);
	}
	if (ft_strncmp(argv[3], "AO", 3) == 0)
	{
		scene->render_mode = RENDER_AO;
		log_event(stdout, "WARN", "Debug mode: Ambient Occlusion\n");
	}
	else if (ft_strncmp(argv[3], "NORMAL", 7) == 0)
	{
		scene->render_mode = RENDER_NORMAL;
		log_event(stdout, "WARN", "Debug mode: Normal Visualization\n");
	}
	else
	{
		print_error_detail(ERR_ARG, argv[3]);
		print_usage();
		clean_exit(scene, EXIT_FAILURE);
	}
}
