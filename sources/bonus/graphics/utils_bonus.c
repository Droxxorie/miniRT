/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:05:49 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 13:06:06 by eraad            ###   ########.fr       */
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

void	image_pixel_put(t_image *image, int x, int y, int color)
{
	char	*pixel_addr;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	pixel_addr = image->addr + ((y * image->line_len) + (x * (image->bpp / 8)));
	*(unsigned int *)pixel_addr = color;
}
