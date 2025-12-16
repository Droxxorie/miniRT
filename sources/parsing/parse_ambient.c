/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:06:32 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 20:34:10 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_status	parse_ambient(t_scene *scene, char **line)
{
	t_real	ratio;

	if (scene->ambient.r != -1)
		return (print_error(ERR_AMBIENT_DUPL), EXIT_FAILURE);
	if (parse_ratio(line, &ratio, FALSE) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (skip_required(line, WHITESPACE_CHARS) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parse_color(line, &scene->ambient) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_eol(line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	scene->ambient = color_scale(scene->ambient, ratio);
	return (EXIT_SUCCESS);
}
