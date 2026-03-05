/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_saturation_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:00:00 by eraad             #+#    #+#             */
/*   Updated: 2026/03/05 22:02:33 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_real	compute_luminance(t_color color)
{
	return (0.299 * color.r + 0.587 * color.g + 0.114 * color.b);
}

static void	apply_saturation_to_pixel(t_image *image, int x, int y,
	t_real factor)
{
	t_color				pixel_color;
	t_real				luminance_value;
	t_real				luminance_blend_factor;

	pixel_color = get_pixel_color(image, x, y);
	luminance_value = compute_luminance(pixel_color);
	luminance_blend_factor = 1.0 - factor;
	pixel_color.r = ft_clamp(pixel_color.r * factor
			+ luminance_value * luminance_blend_factor, 0.0, 1.0);
	pixel_color.g = ft_clamp(pixel_color.g * factor
			+ luminance_value * luminance_blend_factor, 0.0, 1.0);
	pixel_color.b = ft_clamp(pixel_color.b * factor
			+ luminance_value * luminance_blend_factor, 0.0, 1.0);
	image_pixel_put(image, x, y, color_to_int(pixel_color));
}

void	apply_filter_saturation(t_image *image, t_real factor)
{
	int		x;
	int		y;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			apply_saturation_to_pixel(image, x, y, factor);
			x++;
		}
		y++;
	}
}
