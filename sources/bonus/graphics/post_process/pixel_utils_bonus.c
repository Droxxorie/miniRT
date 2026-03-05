/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:00:00 by eraad             #+#    #+#             */
/*   Updated: 2026/03/05 22:02:29 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

unsigned int	get_pixel_from_image(t_image *image, int x, int y)
{
	char	*pixel_addr;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= image->width)
		x = image->width - 1;
	if (y >= image->height)
		y = image->height - 1;
	pixel_addr = image->addr + (y * image->line_len + x * (image->bpp / 8));
	return (*(unsigned int *)pixel_addr);
}

t_color	get_pixel_color(t_image *image, int x, int y)
{
	unsigned int	color_integer;
	t_color			sampled_color;

	color_integer = get_pixel_from_image(image, x, y);
	sampled_color.r = ((color_integer >> 16) & 0xFF) * INV_255;
	sampled_color.g = ((color_integer >> 8) & 0xFF) * INV_255;
	sampled_color.b = (color_integer & 0xFF) * INV_255;
	return (sampled_color);
}
