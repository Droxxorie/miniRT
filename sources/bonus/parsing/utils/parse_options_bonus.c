/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:27:11 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 17:59:07 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_status	parse_options(t_scene *scene, char **line, t_object *object)
{
	while (**line)
	{
		skip_whitespace(line);
		if (**line == '\0' || **line == '#' || **line == '\n')
			return (EXIT_SUCCESS);
		if (match_and_consume(line, "-usemtl") == EXIT_SUCCESS)
		{
			if (parse_usemtl(scene, line, object) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (match_and_consume(line, "-sdf") == EXIT_SUCCESS)
		{
			if (parse_sdf(scene, line, object) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
		{
			print_error_loc(scene, *line, ERR_OPTION);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
