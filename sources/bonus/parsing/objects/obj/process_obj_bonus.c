/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_obj_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:12:05 by eraad             #+#    #+#             */
/*   Updated: 2026/03/07 22:43:25 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_status	dispatch_obj_line(t_scene *scene, t_obj_data *data, char *line)
{
	char	*start_ptr;

	start_ptr = line;
	skip_whitespace(&line);
	if (*line == '\0' || *line == '#' || *line == '\n')
		return (EXIT_SUCCESS);
	if (match_and_consume(&line, "v") == EXIT_SUCCESS)
		return (parse_obj_vertex(scene, data, &line));
	if (match_and_consume(&line, "vt") == EXIT_SUCCESS)
		return (parse_obj_texcoord(scene, data, &line));
	if (match_and_consume(&line, "vn") == EXIT_SUCCESS)
		return (parse_obj_normal(scene, data, &line));
	if (match_and_consume(&line, "f") == EXIT_SUCCESS)
		return (parse_obj_face(scene, data, &line));
	if (match_and_consume(&line, "mtllib") == EXIT_SUCCESS)
		return (parse_obj_mtllib(scene, data, &line));
	if (match_and_consume(&line, "usemtl") == EXIT_SUCCESS)
		return (parse_obj_usemtl(scene, data, &line));
	if (match_and_consume(&line, "o") == EXIT_SUCCESS
		|| match_and_consume(&line, "g") == EXIT_SUCCESS
		|| match_and_consume(&line, "s") == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	print_error_loc(scene, start_ptr, "Unknown identifier in OBJ file");
	return (EXIT_FAILURE);
}

t_status	process_obj_line(t_scene *scene, int fd, t_obj_data *data)
{
	char		*line;
	t_status	status;

	status = EXIT_SUCCESS;
	line = get_next_line(fd);
	while (line)
	{
		scene->line_number++;
		scene->line_ptr = line;
		if (dispatch_obj_line(scene, data, line) == EXIT_FAILURE)
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
