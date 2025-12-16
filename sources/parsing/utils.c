/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:36:09 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 23:02:25 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	skip_whitespace(char **line)
{
	while (**line && ft_iswhitespace(**line))
		(*line)++;
}

t_status	skip_required(char **line, const char *delimiters)
{
	size_t	len;

	len = ft_strspn(*line, delimiters);
	if (len == 0)
	{
		print_error(ERR_PARSE_DELIM);
		return (EXIT_FAILURE);
	}
	*line += len;
	return (EXIT_SUCCESS);
}

t_status	parse_comma(char **line)
{
	skip_whitespace(line);
	if (**line != ',')
	{
		print_error(ERR_PARSE_COMMA);
		return (EXIT_FAILURE);
	}
	(*line)++;
	return (EXIT_SUCCESS);
}

t_status	check_eol(char **line)
{
	skip_whitespace(line);
	if (**line != '\0' && **line != '#')
	//* On garde les commentaires pour le moment
	{
		print_error(ERR_PARSE_EOL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
