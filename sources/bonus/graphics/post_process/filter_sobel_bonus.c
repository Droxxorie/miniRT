/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_sobel_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:00:00 by eraad             #+#    #+#             */
/*   Updated: 2026/03/05 22:02:23 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_real	compute_luminance(t_color color)
{
	return (0.299 * color.r + 0.587 * color.g + 0.114 * color.b);
}

static t_real	luminance_at_pixel(t_image *image, int px, int py)
{
	return (compute_luminance(get_pixel_color(image, px, py)));
}

static t_real	sobel_magnitude_at_pixel(t_image *source_image, int x, int y)
{
	static int		kernel_x[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
	static int		kernel_y[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
	t_vec2			gradient;
	int				index;
	t_real			magnitude;

	gradient.x = 0;
	gradient.y = 0;
	index = 0;
	while (index < 9)
	{
		gradient.x += luminance_at_pixel(source_image,
				x + (index % 3) - 1, y + (index / 3) - 1) * kernel_x[index];
		gradient.y += luminance_at_pixel(source_image,
				x + (index % 3) - 1, y + (index / 3) - 1) * kernel_y[index];
		index++;
	}
	magnitude = sqrtf(gradient.x * gradient.x + gradient.y * gradient.y);
	if (magnitude > 1.0)
		magnitude = 1.0;
	return (magnitude);
}

static void	apply_sobel_to_row(t_image *source_image, t_image *dest_image,
	int row_index)
{
	int		column;
	t_real	magnitude;

	column = 0;
	while (column < source_image->width)
	{
		magnitude = sobel_magnitude_at_pixel(source_image, column, row_index);
		image_pixel_put(dest_image, column, row_index,
			color_to_int((t_color){magnitude, magnitude, magnitude}));
		column++;
	}
}

void	apply_filter_sobel(t_image *src, t_image *dst)
{
	int	row_index;

	row_index = 0;
	while (row_index < src->height)
	{
		apply_sobel_to_row(src, dst, row_index);
		row_index++;
	}
}
