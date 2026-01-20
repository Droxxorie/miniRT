/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_mtl_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:09:02 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 14:30:05 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_status	parse_color_mtl(char **line, t_color *color)
{
	if (parse_real(line, &color->r) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parse_real(line, &color->g) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parse_real(line, &color->b) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	color->r = ft_clamp(color->r, 0.0, 1.0);
	color->g = ft_clamp(color->g, 0.0, 1.0);
	color->b = ft_clamp(color->b, 0.0, 1.0);
	return (EXIT_SUCCESS);
}
