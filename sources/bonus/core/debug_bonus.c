/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:31:04 by eraad             #+#    #+#             */
/*   Updated: 2026/01/22 14:54:10 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	set_mode(t_scene *scene, t_render_mode mode, char *message)
{
	scene->render_mode = mode;
	log_event(stdout, "WARN", "Render mode set to: %s\n", message);
}

static void	dispatch_mode(char **argv, t_scene *scene)
{
	if (ft_strncmp(argv[3], "AO", 3) == 0)
		set_mode(scene, RENDER_AO, "AO");
	else if (ft_strncmp(argv[3], "NORMAL", 7) == 0)
		set_mode(scene, RENDER_NORMAL, "NORMAL");
	else if (ft_strncmp(argv[3], "DEPTH", 6) == 0)
		set_mode(scene, RENDER_DEPTH, "DEPTH");
	else if (ft_strncmp(argv[3], "SHADOWS", 8) == 0)
		set_mode(scene, RENDER_SHADOWS, "SHADOWS");
	else if (ft_strncmp(argv[3], "LIGHTS", 7) == 0)
		set_mode(scene, RENDER_LIGHTS, "LIGHTS");
	else if (ft_strncmp(argv[3], "UV", 3) == 0)
		set_mode(scene, RENDER_UV, "UV");
	else if (ft_strncmp(argv[3], "CHECKER", 8) == 0)
		set_mode(scene, RENDER_CHECKER, "CHECKER");
	else
	{
		print_error_detail(ERR_ARG, argv[3]);
		print_usage();
		clean_exit(scene, EXIT_FAILURE);
	}
}

void	setup_debug_mode(int argc, char **argv, t_scene *scene)
{
	scene->render_mode = RENDER_SHADE;
	if (argc != 4)
	{
		print_error(ERR_DEBUG);
		print_usage();
		clean_exit(scene, EXIT_FAILURE);
	}
	dispatch_mode(argv, scene);
}
