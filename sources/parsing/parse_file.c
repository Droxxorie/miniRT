/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:13:00 by eraad             #+#    #+#             */
/*   Updated: 2025/12/10 22:32:18 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_status	match_identifier(const char *line, const char *identifier)
{
	size_t	len;

	len = ft_strlen(identifier);
	if (ft_strncmp(line, identifier, len) != 0)
		return (EXIT_FAILURE);
	if (line[len] != '\0' && !ft_isspace(line[len]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// static char	*extract_identifier(char **line)
// {
// 	char	*identifier;
// 	int		len;
// 	int		index;

// 	index = 0;
// 	*line += ft_strspn(*line, WHITESPACE_CHARS);
// 	if (**line == '\0')
// 		return (NULL);
// 	len = ft_strcspn(*line, WHITESPACE_CHARS);
// 	if (len == 0)
// 		return (NULL);
// 	identifier = (char *)ft_calloc(sizeof(char), (len + 1));
// 	ft_strncpy(identifier, *line, len);
// 	*line += len;
// 	*line += ft_strspn(*line, WHITESPACE_CHARS);
// 	return (identifier);
// }

static t_status	dispatch_parse(t_scene *scene, char *line, int line_index)
{
	int					i;
	static t_parse_map	parse_map[] = {{"A", parse_ambient}, {"C",
			parse_camera}, {"L", parse_light}, {"sp",
			parse_sphere}, {"pl", parse_plane}, {"cy", parse_cylinder}, {NULL, NULL}};

	// while (*line && ft_isspace(*line))
	// 	line++;
	skip_whitespace(&line);
	if (*line == '\0' || *line == '#') //* skip empty lines and comments
		return (EXIT_SUCCESS);
	i = 0;
	while (parse_map[i].id)
	{
		if (match_identifier(*line, parse_map[i].id) == EXIT_SUCCESS)
		{
			line += ft_strlen(parse_map[i].id);
			return (parse_map[i].func(scene, &line));
		}
		i++;
	}
	print_error(ERR_PARSE_UID);
	ft_printf_fd(STDERR_FILENO, "Line %d: %s\n", line_index, line);
	return (EXIT_FAILURE);
}

// static t_bool	dispatch_parse(t_scene *scene, char **line)
// {
// 	char				*identifier;
// 	int					i;
// 	static t_parse_map	parse_map[] = {
// 		{"A", parse_ambient},
// 		{"C", parse_camera},
// 		{"L", parse_light},
// 		{"R", parse_resolution},
// 		{"sp", parse_sphere},
// 		{"pl", parse_plane},
// 		{"cy", parse_cylinder},
// 		{"sq", parse_square},
// 		{"tr", parse_triangle},
// 		{NULL, NULL}};

// 	i = 0;
// 	identifier = extract_identifier(line);
// 	if (!identifier)
// 		return (TRUE);
// 	while (parse_map[i].id && ft_strcmp(identifier, parse_map[i].id) != 0)
// 		i++;
// 	free(identifier);
// 	if (!parse_map[i].id)
// 		return (error_msg(ERR_PAR_NOID));
// 	return (parse_map[i].func(scene, line));
// }

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

	fd = open(file_path, O_RDONLY);
	if (fd < 0) //? ou < 3 pour tt couvrir ?
		return (sys_print_error(ERR_FILE_OPEN), EXIT_FAILURE);
	if (has_extension(file_path, ".rt") == FALSE)
		return (close(fd),print_error(ERR_FILE_FORMAT), EXIT_FAILURE);
	line = get_next_line(fd);
	line_index = 1;
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
