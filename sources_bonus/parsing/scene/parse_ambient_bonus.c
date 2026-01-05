/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:06:32 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:42:18 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_status	parse_ambient(t_scene *scene, char **line)
{
	t_real	ratio;

	if (scene->ambient.r != -1)
	{
		print_error_loc(scene, *line - 1, ERR_AMBIENT_DUP);
		return (EXIT_FAILURE);
	}
	if (parse_ratio(scene, line, &ratio, FALSE) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (skip_required(scene, line, WHITESPACE_CHARS) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parse_color(scene, line, &scene->ambient) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_eol(scene, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	scene->ambient = color_scale(scene->ambient, ratio);
	return (EXIT_SUCCESS);
}
