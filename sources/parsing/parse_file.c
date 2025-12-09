/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:13:00 by eraad             #+#    #+#             */
/*   Updated: 2025/12/09 21:08:42 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_bool	match_identifier(const char *line, const char *identifier)
{
	size_t	id_len;

	id_len = ft_strlen(identifier);
	if (ft_strncmp(line, identifier, id_len) == 0)
		return (TRUE);
	return (FALSE);
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

static t_bool	dispatch_parse(t_scene *scene, char **line)
{
	int					i;
	static t_parse_map	parse_map[] = {{"A", parse_ambient}, {"C",
		parse_camera}, {"L", parse_light}, {"R", parse_resolution}, {"sp",
		parse_sphere}, {"pl", parse_plane}, {"cy", parse_cylinder}, {"sq",
		parse_square}, {"tr", parse_triangle}, {NULL, NULL}};

	while (*line && ft_isspace(**line))
		(*line)++;
	if (**line == '\0')
		return (TRUE);
	i = 0;
	while (parse_map[i].id)
	{
		if (match_identifier(*line, parse_map[i].id))
		{
			*line += ft_strlen(parse_map[i].id);
			return (parse_map[i].func(scene, line));
		}
		i++;
	}
	return (error_msg(ERR_FILE_FORMAT)); // TODO
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
// 	identifier = extract_identifier(line); // TODO
// 	if (!identifier)
// 		return (TRUE);
// 	while (parse_map[i].id && ft_strcmp(identifier, parse_map[i].id) != 0)
// 		i++;
// 	free(identifier);
// 	if (!parse_map[i].id)
// 		return (error_msg(ERR_PAR_NOID)); // TODO
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

t_bool	parse_scene_file(t_scene *scene, const char *file_path)
{
	int		fd;
	char	*line;
	int		ret;

	ret = TRUE;
	fd = open(file_path, O_RDONLY);
	if (fd < 3)
		return (sys_print_error(ERR_FILE_OPEN), FALSE);
	if (has_extension(file_path, ".rt") == FALSE)
		return (print_error(ERR_FILE_FORMAT), FALSE);
	line = get_next_line(fd);
	while (line)
	{
		if (!dispatch_parse(scene, line)) // TODO
			ret = error_line(line);       // TODO
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (ret);
}
