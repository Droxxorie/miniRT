/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_sepia_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:00:00 by eraad             #+#    #+#             */
/*   Updated: 2026/03/05 22:02:14 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_color	apply_sepia_to_pixel_color(t_color pixel_color)
{
	t_color	sepia_color;

	sepia_color.r = ft_clamp(0.393 * pixel_color.r + 0.769 * pixel_color.g
			+ 0.189 * pixel_color.b, 0.0, 1.0);
	sepia_color.g = ft_clamp(0.349 * pixel_color.r + 0.686 * pixel_color.g
			+ 0.168 * pixel_color.b, 0.0, 1.0);
	sepia_color.b = ft_clamp(0.272 * pixel_color.r + 0.534 * pixel_color.g
			+ 0.131 * pixel_color.b, 0.0, 1.0);
	return (sepia_color);
}

void	apply_filter_sepia(t_image *image)
{
	int		x;
	int		y;
	t_color	pixel_color;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			pixel_color = get_pixel_color(image, x, y);
			image_pixel_put(image, x, y,
				color_to_int(apply_sepia_to_pixel_color(pixel_color)));
			x++;
		}
		y++;
	}
}
