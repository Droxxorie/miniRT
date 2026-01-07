/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:04:46 by eraad             #+#    #+#             */
/*   Updated: 2026/01/07 00:38:18 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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
	if ((argc == 3 || argc == 4) && ft_strncmp(argv[2], "--save", 7) != 0)
	{
		print_error_detail(ERR_ARG, argv[2]);
		ret = TRUE;
	}
	scene->to_save = TRUE;
	scene->save_file = "saved/output.bmp";
	if (argc == 4)
		// scene->save_file = argv[3];
		scene->save_file = ft_strjoin("saved/", argv[3]);
	if (check_save_file(scene) == EXIT_FAILURE)
		ret = TRUE;
	if (ret == TRUE)
	{
		ft_putstr_fd("\n", 1);
		print_usage();
		clean_exit(scene, EXIT_FAILURE);
	}
	log_detail("Save file: ", scene->save_file);
}

static void write_bmp_header(int fd, int width, int height)
{
	char	header[54];

	ft_bzero(header, 54);
	header[0] = 'B';
	header[1] = 'M'; //* signature
	*(int *)&header[2] = 54 + (width * height * 4); //* file size
	*(int *)&header[10] = 54; //* offset to pixel data
	*(int *)&header[14] = 40; //* info header size
	*(int *)&header[18] = width; //* image width
	*(int *)&header[22] = -height; //* top-down bitmap
	*(short *)&header[26] = 1; //* plane
	*(short *)&header[28] = 32; //* bits per pixel
	if (write(fd, header, 54) < 0)
	{
		sys_print_error("caca"); //TODO enlever
		return ;
	}
}

void	save_image_to_bmp(t_scene *scene)
{
	int		fd;
	int		y;
	char	*line_ptr;
	int		line_len;

	log_detail("Saving rendered image to file: ", scene->save_file);
	fd = open(scene->save_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		sys_print_error_free_exit(scene, ERR_SAVE_FILE);
	write_bmp_header(fd, scene->mlx_window.width, scene->mlx_window.height); //TODO if
	line_len = scene->mlx_window.width * 4;
	y = 0;
	while (y < scene->mlx_window.height)
	{
		display_progress(y, scene->mlx_window.height - 1);
		line_ptr = scene->frame_buffer.addr + (y * scene->frame_buffer.line_len);
		if (write(fd, line_ptr, line_len) < 0)
		{
			close(fd);
			sys_print_error_free_exit(scene, "ERROR SAVE"); //TODO chnger msg
		}
		y++;
	}
	close(fd);
	log_info("Image saved successfully!");
	clean_exit(scene, EXIT_SUCCESS);
}
