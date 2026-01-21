/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_texture_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:40:53 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 20:00:37 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static unsigned int	get_pixel_int(t_image *image, int x, int y)
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

t_color	sample_texture(t_image *texture, t_real u, t_real v)
{
	int				x;
	int				y;
	unsigned int	color_int;
	t_color			color;

	if (!texture || !texture->ptr)
		return ((t_color){1.0, 0.0, 1.0});
	u = u - floor(u);
	v = v - floor(v);
	x = (int)(u * (t_real)(texture->width - 1));
	y = (int)((1.0 - v) * (t_real)(texture->height - 1));
	color_int = get_pixel_int(texture, x, y);
	color.r = ((color_int >> 16) & 0xFF) * INV_255;
	color.g = ((color_int >> 8) & 0xFF) * INV_255;
	color.b = (color_int & 0xFF) * INV_255;
	return (color);
}
