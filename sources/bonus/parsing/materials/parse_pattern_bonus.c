/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pattern_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 19:44:11 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 20:48:23 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_status	parse_pattern(char **line, t_material *material)
{
	skip_whitespace(line);
	if (match_and_consume(line, "checker") == EXIT_SUCCESS)
		material->pattern_type = PATTERN_CHECKER;
	else if (match_and_consume(line, "rainbow") == EXIT_SUCCESS)
		material->pattern_type = PATTERN_RAINBOW;
	else if (match_and_consume(line, "wave") == EXIT_SUCCESS)
		material->pattern_type = PATTERN_WAVE;
	else if (match_and_consume(line, "perlin") == EXIT_SUCCESS)
		material->pattern_type = PATTERN_PERLIN_NOISE;
	else if (match_and_consume(line, "marble") == EXIT_SUCCESS)
		material->pattern_type = PATTERN_MARBLE;
	else
		return (print_error("Unknown pattern type"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
