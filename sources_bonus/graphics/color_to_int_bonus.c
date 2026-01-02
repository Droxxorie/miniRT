/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_to_int_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:43:50 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:39:42 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static int	to_byte(t_real color_component)
{
	int	byte_value;

	byte_value = (int)(color_component * 255.999);
	if (byte_value > 255)
		return (255);
	if (byte_value < 0)
		return (0);
	return (byte_value);
}

int	color_to_int(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = to_byte(color.r);
	g = to_byte(color.g);
	b = to_byte(color.b);
	return ((r << 16) | (g << 8) | b);
}
