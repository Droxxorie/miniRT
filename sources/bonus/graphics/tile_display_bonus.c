/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile_display_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 20:00:00 by eraad             #+#    #+#             */
/*   Updated: 2026/03/03 22:54:09 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	draw_h_line(t_image *img, int start[2], int len, int color)
{
	int	i;

	i = 0;
	while (i < len)
	{
		image_pixel_put(img, start[0] + i, start[1], color);
		i++;
	}
}

static void	draw_v_line(t_image *img, int start[2], int len, int color)
{
	int	i;

	i = 0;
	while (i < len)
	{
		image_pixel_put(img, start[0], start[1] + i, color);
		i++;
	}
}

void	draw_tile_border(t_scene *s, int x, int y)
{
	int	scale;
	int	w;
	int	h;
	int	pt[2];

	scale = (int)s->render_scale;
	if (scale < 1)
		scale = 1;
	w = TILE_SIZE * scale;
	h = w;
	if (x + w > s->mlx_window.width)
		w = s->mlx_window.width - x;
	if (y + h > s->mlx_window.height)
		h = s->mlx_window.height - y;
	pt[0] = x;
	pt[1] = y;
	draw_h_line(&s->frame_buffer, pt, w, BORDER_COLOR);
	pt[1] = y + h - 1;
	draw_h_line(&s->frame_buffer, pt, w, BORDER_COLOR);
	pt[1] = y;
	draw_v_line(&s->frame_buffer, pt, h, BORDER_COLOR);
	pt[0] = x + w - 1;
	draw_v_line(&s->frame_buffer, pt, h, BORDER_COLOR);
}
