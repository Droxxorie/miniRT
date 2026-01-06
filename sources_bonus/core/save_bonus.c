/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:04:46 by eraad             #+#    #+#             */
/*   Updated: 2026/01/06 17:58:16 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_bool	has_save_flag(int argc, char **argv)
{
	if ((argc == 3 || argc == 4) && ft_strncmp(argv[2], "--save", 7) == 0)
		return (TRUE);
	return (FALSE);
}

static	t_status	check_save_file(t_scene *scene)
{
	int fd;

	if (has_extension(scene->save_file, ".bmp") == FALSE)
	{
		print_error_detail(ERR_SAVE_EXT, scene->save_file);
		clean_exit(scene, EXIT_FAILURE);
	}
	fd = open(scene->save_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		close(fd);
		sys_print_error(ERR_SAVE_FILE);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

void	setup_save_mode(int argc, char **argv, t_scene *scene)
{
	t_bool	ret;
	
	ret = FALSE;
	log_info("Setting up save mode...");
	if (has_save_flag(argc, argv) == FALSE)
	{
		print_error_detail(ERR_ARG, argv[2]);
		ret = TRUE;
	}
	scene->to_save = TRUE;
	scene->save_file = "output.bmp";
	if (argc == 4)
		scene->save_file = argv[3];
	if (check_save_file(scene) == EXIT_FAILURE)
		ret = TRUE;
	if (ret == TRUE)
	{
		ft_putstr_fd("\n", 1);
		print_usage();
		clean_exit(scene, EXIT_FAILURE);
	}
}
