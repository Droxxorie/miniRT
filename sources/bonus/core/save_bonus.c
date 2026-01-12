/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:04:46 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 16:09:46 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_status	check_save_file(t_scene *scene)
{
	int	fd;

	if (has_extension(scene->save_file, ".bmp") == FALSE)
	{
		print_error_detail(ERR_SAVE_EXT, scene->save_file);
		return (EXIT_FAILURE);
	}
	if (mkdir("saved", 0755) == 0)
	{
		log_event(stdout, "WARN", "'saved' directory do not exist\n");
		log_event(stdout, "INFO",
			"Created 'saved' directory for output files\n");
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
	if ((argc == 3 || argc == 4) && ft_strncmp(argv[2], "--save", 7) != 0)
	{
		print_error_detail(ERR_ARG, argv[2]);
		ret = TRUE;
	}
	scene->to_save = TRUE;
	if (argc == 4)
		scene->save_file = ft_strjoin("saved/", argv[3]);
	else
		scene->save_file = ft_strdup("saved/output.bmp");
	if (check_save_file(scene) == EXIT_FAILURE)
		ret = TRUE;
	if (ret == TRUE)
	{
		print_usage();
		clean_exit(scene, EXIT_FAILURE);
	}
}

static t_status	write_bmp_header(int fd, int width, int height)
{
	char	header[54];
	int		bpp;
	int		plane;
	int		offset;
	int		file_size;

	ft_bzero(header, 54);
	header[0] = 'B';
	header[1] = 'M';
	bpp = 32;
	plane = 1;
	offset = 54;
	file_size = offset + (width * height * 4);
	*(int *)&header[2] = file_size;
	*(int *)&header[10] = offset;
	*(int *)&header[14] = 40;
	*(int *)&header[18] = width;
	*(int *)&header[22] = -height;
	*(short *)&header[26] = plane;
	*(short *)&header[28] = bpp;
	if (write(fd, header, 54) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static t_status	write_pixel_data(int fd, t_scene *scene)
{
	int		y;
	int		line_len;
	char	*pixel_ptr;

	line_len = scene->frame_buffer.line_len;
	y = 0;
	while (y < scene->mlx_window.height)
	{
		display_progress(y, scene->mlx_window.height - 1);
		pixel_ptr = scene->frame_buffer.addr + (y * line_len);
		if (write(fd, pixel_ptr, line_len) < 0)
			return (EXIT_FAILURE);
		y++;
	}
	return (EXIT_SUCCESS);
}

void	save_image_to_bmp(t_scene *scene)
{
	int	fd;
	int	status;

	log_event(stdout, "INFO", "Saving image to BMP file: %s%s%s\n", UNDERLINE,
		scene->save_file, RESET);
	fd = open(scene->save_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		sys_print_error_free_exit(scene, ERR_SAVE_FILE);
	status = write_bmp_header(fd, scene->mlx_window.width,
			scene->mlx_window.height);
	if (status != EXIT_FAILURE)
		status = write_pixel_data(fd, scene);
	close(fd);
	if (status == EXIT_FAILURE)
		sys_print_error_free_exit(scene, ERR_WRITE);
	log_event(stdout, "SUCCESS", "Image saved successfully!\n");
}
