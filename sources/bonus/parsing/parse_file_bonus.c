/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:13:00 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 16:38:19 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_status	match_identifier(const char *line, const char *identifier)
{
	size_t	len;

	len = ft_strlen(identifier);
	if (ft_strncmp(line, identifier, len) != 0)
		return (EXIT_FAILURE);
	if (line[len] != '\0' && !ft_iswhitespace(line[len]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static t_status	dispatch_parse(t_scene *scene, char *line)
{
	int					i;
	char				*start_ptr;
	static t_parse_map	map[] = {{"R", parse_resolution}, {"A", parse_ambient},
	{"C", parse_camera}, {"L", parse_light}, {"sp", parse_sphere},
	{"pl", parse_plane}, {"cy", parse_cylinder},
	{"rec", parse_rectangle}, {"dis", parse_disk}, {"tri", parse_triangle},
	{"tor", parse_torus}, {"con", parse_cone}, {"box", parse_box},
	{NULL, NULL}};

	skip_whitespace(&line);
	if (*line == '\0' || *line == '#')
		return (EXIT_SUCCESS);
	start_ptr = line;
	i = 0;
	while (map[i].id)
	{
		if (match_identifier(line, map[i].id) == EXIT_SUCCESS)
		{
			line += ft_strlen(map[i].id);
			return (map[i].func(scene, &line));
		}
		i++;
	}
	print_error_loc(scene, start_ptr, ERR_UID);
	return (EXIT_FAILURE);
}

t_bool	has_extension(const char *file, const char *extension)
{
	size_t	file_len;
	size_t	ext_len;

	if (!file || !extension)
		return (FALSE);
	file_len = ft_strlen(file);
	ext_len = ft_strlen(extension);
	if (file_len < ext_len)
		return (FALSE);
	return (ft_strncmp(file + file_len - ext_len, extension, ext_len) == 0);
}

t_status	parse_scene_file(t_scene *scene, const char *file_path)
{
	int		fd;
	char	*line;

	if (has_extension(file_path, ".rt") == FALSE)
		return (print_error(ERR_FILE_EXT), EXIT_FAILURE);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (sys_print_error(file_path), EXIT_FAILURE);
	if (read(fd, 0, 0) < 0)
		return (sys_print_error(file_path), close(fd), EXIT_FAILURE);
	line = get_next_line(fd);
	if (!line)
		return (print_error(ERR_EMPTY), close(fd), EXIT_FAILURE);
	scene->line_number = 1;
	while (line)
	{
		scene->line_ptr = line;
		if (dispatch_parse(scene, line) == EXIT_FAILURE)
			return (consume_gnl(fd, &line), close(fd), EXIT_FAILURE);
		free(line);
		line = get_next_line(fd);
		scene->line_number++;
	}
	close(fd);
	return (EXIT_SUCCESS);
}
