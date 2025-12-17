/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:13:00 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 07:46:55 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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

static t_status	dispatch_parse(t_scene *scene, char *line, int line_index)
{
	int					i;
	static t_parse_map	map[] = {
	{"A", parse_ambient},
	{"C", parse_camera},
	{"L", parse_light},
	{"sp", parse_sphere},
	{"pl", parse_plane},
	{"cy", parse_cylinder}, {NULL, NULL}};

	skip_whitespace(&line);
	if (*line == '\0' || *line == '#')
		return (EXIT_SUCCESS);
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
	print_error(ERR_PARSE_UID);
	ft_printf_fd(STDERR_FILENO, "Line %d: %s\n", line_index, line);
	return (EXIT_FAILURE);
}

static t_bool	has_extension(const char *file, const char *extension)
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
	int		line_index;

	if (has_extension(file_path, ".rt") == FALSE)
		return (print_error(ERR_FILE_FORMAT), EXIT_FAILURE);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (sys_print_error(ERR_FILE_OPEN), EXIT_FAILURE);
	line_index = 1;
	line = get_next_line(fd);
	while (line)
	{
		if (dispatch_parse(scene, line, line_index) == EXIT_FAILURE)
		{
			free(line);
			close(fd);
			return (EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
		line_index++;
	}
	close(fd);
	return (EXIT_SUCCESS);
}
