/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_bnw_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:00:00 by eraad             #+#    #+#             */
/*   Updated: 2026/03/05 22:01:51 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_real	luminance(t_color color)
{
	return (0.299 * color.r + 0.587 * color.g + 0.114 * color.b);
}

void	apply_filter_bnw(t_image *image)
{
	int		x;
	int		y;
	t_color	pixel_color;
	t_real	luminance_value;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			pixel_color = get_pixel_color(image, x, y);
			luminance_value = luminance(pixel_color);
			image_pixel_put(image, x, y,
				color_to_int((t_color){luminance_value, luminance_value,
					luminance_value}));
			x++;
		}
		y++;
	}
}
