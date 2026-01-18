/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dim_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:16:59 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 15:39:53 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_status	parse_dim(t_scene *scene, char **line, t_real *dim)
{
	char	*start_line;

	start_line = *line;
	if (parse_real(line, dim) == EXIT_FAILURE)
		return (print_error_loc(scene, start_line, ERR_DIM), EXIT_FAILURE);
	if (*dim <= 0)
		return (print_error_loc(scene, start_line, ERR_DIM_OOB), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_status	parse_dim_relative(t_scene *scene, char **line, t_real *dim)
{
	char	*start_line;

	start_line = *line;
	if (parse_real(line, dim) == EXIT_FAILURE)
		return (print_error_loc(scene, start_line, ERR_DIM), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
