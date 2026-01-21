/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_skybox_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 22:06:41 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 22:54:24 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_status	parse_skybox(t_scene *scene, char **line)
{
	char	*path;

	printf("Parsing skybox...\n");
	if (scene->skybox_texture_path != NULL)
	{
		print_error_loc(scene, *line - 1, ERR_SKYBOX_DUP);
		return (EXIT_FAILURE);
	}
	path = extract_string(line);
	if (path == NULL)
		return (sys_print_error(ERR_MEM), EXIT_FAILURE);
	scene->skybox_texture_path = path;
	return (EXIT_SUCCESS);
}
