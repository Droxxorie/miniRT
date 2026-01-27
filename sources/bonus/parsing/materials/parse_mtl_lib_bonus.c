/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mtl_lib_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:44:52 by eraad             #+#    #+#             */
/*   Updated: 2026/01/26 16:36:57 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static int	open_mtl_file(t_scene *scene, char *raw_line, char **filename)
{
	int	fd;

	*filename = extract_string(&raw_line);
	if (*filename == NULL)
		return (print_error(ERR_MEM), -1);
	if (has_extension(*filename, ".mtl") == FALSE)
	{
		print_error_loc(scene, raw_line, ERR_MTL_EXT);
		free(*filename);
		return (-1);
	}
	fd = open(*filename, O_RDONLY);
	if (fd < 0)
	{
		print_error_loc(scene, raw_line, ERR_MTL_FILE);
		free(*filename);
		return (-1);
	}
	return (fd);
}

static t_status	process_mtl_line(t_scene *scene, int fd)
{
	char		*line;
	t_material	*current;
	t_status	status;

	current = NULL;
	status = EXIT_SUCCESS;
	line = get_next_line(fd);
	while (line)
	{
		scene->line_number++;
		scene->line_ptr = line;
		if (dispatch_mtl_line(scene, &current, line) == EXIT_FAILURE)
		{
			status = EXIT_FAILURE;
			consume_gnl(fd, &line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (status);
}

t_status	parse_mtl_lib(t_scene *scene, char **line)
{
	char		*filename;
	int			fd;
	char		*saved_file;
	int			saved_line;
	t_status	status;

	fd = open_mtl_file(scene, *line, &filename);
	if (fd < 0)
		return (EXIT_FAILURE);
	saved_file = scene->file_name;
	saved_line = scene->line_number;
	scene->file_name = filename;
	scene->line_number = 0;
	status = process_mtl_line(scene, fd);
	scene->file_name = saved_file;
	scene->line_number = saved_line;
	close(fd);
	free(filename);
	return (status);
}
