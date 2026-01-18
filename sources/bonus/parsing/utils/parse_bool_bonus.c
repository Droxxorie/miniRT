/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bool_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:38:12 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 13:46:13 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_status	parse_bool(t_scene *scene, char **line, t_bool *value)
{
	char	*start_ptr;

	start_ptr = *line;
	if (ft_strncmp(*line, "TRUE", 4) == 0)
	{
		*value = TRUE;
		*line += 4;
	}
	else if (ft_strncmp(*line, "FALSE", 5) == 0)
	{
		*value = FALSE;
		*line += 5;
	}
	else
		return (print_error_loc(scene, start_ptr, ERR_BOOL), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
