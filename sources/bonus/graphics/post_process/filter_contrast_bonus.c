/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_contrast_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 11:24:13 by eraad             #+#    #+#             */
/*   Updated: 2026/03/05 22:01:46 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_real	apply_contrast_to_channel(t_real channel_value, t_real factor)
{
	return (ft_clamp((channel_value - 0.5) * factor + 0.5, 0.0, 1.0));
}

void	apply_filter_contrast(t_image *image, t_real factor)
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
			pixel_color.r = apply_contrast_to_channel(pixel_color.r, factor);
			pixel_color.g = apply_contrast_to_channel(pixel_color.g, factor);
			pixel_color.b = apply_contrast_to_channel(pixel_color.b, factor);
			image_pixel_put(image, x, y, color_to_int(pixel_color));
			x++;
		}
		y++;
	}
}
