/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:58:27 by eraad             #+#    #+#             */
/*   Updated: 2026/01/05 20:58:43 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_bool	is_valid_dim(int dim, int max)
{
	if (dim <= 0)
		return (FALSE);
	if (dim > max)
		return (FALSE);
	return (TRUE);
}

t_status	parse_resolution(t_scene *scene, char **line)
{
	char	*start_ptr;

	if (scene->mlx_window.width != -1 && scene->mlx_window.height != -1)
	{
		print_error_loc(scene, *line - 1, ERR_RES_DUP);
		return (EXIT_FAILURE);
	}
	start_ptr = *line;
	if (parse_int(line, &scene->mlx_window.width) == EXIT_FAILURE)
		return (print_error_loc(scene, start_ptr, ERR_RES_WITDH), 1);
	if (is_valid_dim(scene->mlx_window.width, MAX_WINDOW_WIDTH) == FALSE)
		return (print_error_loc(scene, start_ptr + 1, ERR_RES_WITDH_OOB), 1);
	start_ptr = *line;
	if (parse_int(line, &scene->mlx_window.height) == EXIT_FAILURE)
		return (print_error_loc(scene, start_ptr, ERR_RES_HEIGHT), 1);
	if (is_valid_dim(scene->mlx_window.height, MAX_WINDOW_HEIGHT) == FALSE)
		return (print_error_loc(scene, start_ptr + 1, ERR_RES_HEIGHT_OOB), 1);
	scene->mlx_window.aspect_ratio = (t_real)scene->mlx_window.width
		/ (t_real)scene->mlx_window.height;
	if (check_eol(scene, line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
