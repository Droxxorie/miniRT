/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:36:09 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 14:39:56 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	skip_whitespace(char **line)
{
	while (**line && ft_iswhitespace(**line))
		(*line)++;
}

t_status	skip_required(t_scene *scene, char **line, const char *delimiters)
{
	size_t	len;

	len = ft_strspn(*line, delimiters);
	if (len == 0)
	{
		print_error_loc(scene, *line, ERR_DELIM);
		return (EXIT_FAILURE);
	}
	*line += len;
	return (EXIT_SUCCESS);
}

t_status	parse_comma(t_scene *scene, char **line)
{
	skip_whitespace(line);
	if (**line != ',')
	{
		print_error_loc(scene, *line, ERR_COMMA);
		return (EXIT_FAILURE);
	}
	(*line)++;
	return (EXIT_SUCCESS);
}

t_status	check_eol(t_scene *scene, char **line)
{
	skip_whitespace(line);
	if (**line != '\0' && **line != '#')
	{
		print_error_loc(scene, *line, ERR_EOL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_status	match_and_consume(char **line, const char *identifier)
{
	size_t	len;

	len = ft_strlen(identifier);
	if (ft_strncmp(*line, identifier, len) != 0)
		return (EXIT_FAILURE);
	if ((*line)[len] != '\0' && !ft_iswhitespace((*line)[len]))
		return (EXIT_FAILURE);
	*line += len;
	return (EXIT_SUCCESS);
}
