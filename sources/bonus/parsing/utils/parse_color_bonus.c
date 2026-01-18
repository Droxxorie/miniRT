/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:36:10 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 13:38:03 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_bool	is_valid_color_value(int value)
{
	return (value >= 0 && value <= 255);
}

static void	assign_color_values(t_color *color, int rgb[3])
{
	color->r = (t_real)rgb[0] * INV_255;
	color->g = (t_real)rgb[1] * INV_255;
	color->b = (t_real)rgb[2] * INV_255;
}

t_status	parse_color(t_scene *scene, char **line, t_color *color)
{
	int		rgb[3];
	char	*start_ptr;

	start_ptr = *line;
	if (parse_int(line, &rgb[0]) == EXIT_FAILURE)
		return (print_error_loc(scene, start_ptr, ERR_RED), 1);
	if (is_valid_color_value(rgb[0]) == FALSE)
		return (print_error_loc(scene, start_ptr, ERR_RED_OOB), 1);
	if (parse_comma(scene, line) == EXIT_FAILURE)
		return (1);
	start_ptr = *line;
	if (parse_int(line, &rgb[1]) == EXIT_FAILURE)
		return (print_error_loc(scene, start_ptr, ERR_GREEN), 1);
	if (is_valid_color_value(rgb[1]) == FALSE)
		return (print_error_loc(scene, start_ptr, ERR_GREEN_OOB), 1);
	if (parse_comma(scene, line) == EXIT_FAILURE)
		return (1);
	start_ptr = *line;
	if (parse_int(line, &rgb[2]) == EXIT_FAILURE)
		return (print_error_loc(scene, start_ptr, ERR_BLUE), 1);
	if (is_valid_color_value(rgb[2]) == FALSE)
		return (print_error_loc(scene, start_ptr, ERR_BLUE_OOB), 1);
	assign_color_values(color, rgb);
	return (EXIT_SUCCESS);
}
