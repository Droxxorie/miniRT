/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:12:05 by eraad             #+#    #+#             */
/*   Updated: 2026/03/07 18:45:18 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_status	check_opt(char **line)
{
	skip_whitespace(line);
	if (**line == '\0' || **line == '\n' || **line == '#')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static t_status	parse_obj_params(t_scene *scene, char **line,
		t_obj_data *data, char *filename)
{
	if (check_opt(line) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	if (parse_vec3(scene, line, &data->position) == EXIT_FAILURE)
		return (free(filename), EXIT_FAILURE);
	if (check_opt(line) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	if (parse_axis(scene, line, &data->rotation) == EXIT_FAILURE)
		return (free(filename), EXIT_FAILURE);
	if (check_opt(line) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	if (parse_real(line, &data->scale) == EXIT_FAILURE)
		return (free(filename), EXIT_FAILURE);
	if (check_opt(line) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	if (parse_color(scene, line, &data->base_color) == EXIT_FAILURE
		|| check_eol(scene, line) == EXIT_FAILURE)
		return (free(filename), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static t_status	get_obj_values(t_scene *scene, char **line,
		t_obj_data *data, char **filename)
{
	*filename = extract_string(line);
	if (*filename == NULL)
		return (print_error(ERR_MEM), EXIT_FAILURE);
	if (has_extension(*filename, ".obj") == FALSE)
	{
		print_error_loc(scene, *line, "Invalid OBJ file extension");
		return (free(*filename), EXIT_FAILURE);
	}
	data->position = (t_point3){0, 0, 0};
	data->rotation = (t_vec3){0, 1, 0};
	data->scale = 1.0;
	data->base_color = (t_color){255, 255, 255};
	return (parse_obj_params(scene, line, data, *filename));
}

static t_status	parse_obj_core(t_scene *scene, t_obj_data *data, char *filename)
{
	int			fd;
	char		*saved_file;
	int			saved_line;
	t_status	status;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || read(fd, 0, 0) < 0)
	{
		if (fd >= 0)
			close(fd);
		print_error_loc(scene, scene->line_ptr, "Cannot open OBJ file");
		sys_print_error(filename);
		return (EXIT_FAILURE);
	}
	saved_file = scene->file_name;
	saved_line = scene->line_number;
	scene->file_name = filename;
	scene->line_number = 0;
	status = process_obj_line(scene, fd, data);
	scene->file_name = saved_file;
	scene->line_number = saved_line;
	close(fd);
	return (status);
}

t_status	parse_obj(t_scene *scene, char **line)
{
	t_obj_data	data;
	char		*filename;
	t_status	status;

	ft_bzero(&data, sizeof(t_obj_data));
	if (get_obj_values(scene, line, &data, &filename) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	status = parse_obj_core(scene, &data, filename);
	free(filename);
	free(data.v_array);
	free(data.vt_array);
	free(data.vn_array);
	return (status);
}
