/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sdf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 10:33:32 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 14:04:42 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_status	parse_sdf(t_scene *scene, char **line, t_bool *is_sdf)
{
	skip_whitespace(line);
	if (**line == '\0' || **line == '#' || **line == '\n')
	{
		*is_sdf = FALSE;
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(*line, "-sdf", 4) == 0)
	{
		*line += 4;
		*is_sdf = TRUE;
		return (EXIT_SUCCESS);
	}
	print_error_loc(scene, *line, "Invalid identifier, expected '-sdf'");
	return (EXIT_FAILURE);
}
