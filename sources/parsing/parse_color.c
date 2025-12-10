/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:36:10 by eraad             #+#    #+#             */
/*   Updated: 2025/12/10 22:30:16 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_bool	is_valid_color_value(int value)
{
	return (value >= 0 && value <= 255);
}

t_status	parse_color(char **line, t_color *color)
{
	int	red;
	int	green;
	int	blue;

	if (parse_int(line, &red) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parse_comma(line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parse_int(line, &green) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parse_comma(line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parse_int(line, &blue) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!is_valid_color_value(red)
		|| !is_valid_color_value(green)
		|| !is_valid_color_value(blue))
		return (print_error(ERR_COLOR_RANGE), EXIT_FAILURE);
	// color->r = (t_real)red / 255.0;
	// color->g = (t_real)green / 255.0;
	// color->b = (t_real)blue / 255.0;
	color->r = (t_real)red * INV_255;
	color->g = (t_real)green * INV_255;
	color->b = (t_real)blue * INV_255;
	return (EXIT_SUCCESS);
}
