/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_gaussian_blur_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:45:43 by eraad             #+#    #+#             */
/*   Updated: 2026/03/06 00:45:45 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	put_blurred_pixel(t_gauss_ctx *ctx, int row_index, int column_index,
		int is_horizontal)
{
	t_w_result	result;
	t_color		clamped;

	if (is_horizontal)
		result = get_weighted_sum_horizontal(ctx, row_index, column_index);
	else
		result = get_weighted_sum_vertical(ctx, column_index, row_index);
	if (result.total > 0)
	{
		clamped.r = ft_clamp(result.sum.r / result.total, 0.0, 1.0);
		clamped.g = ft_clamp(result.sum.g / result.total, 0.0, 1.0);
		clamped.b = ft_clamp(result.sum.b / result.total, 0.0, 1.0);
	}
	else
		clamped = (t_color){0, 0, 0};
	image_pixel_put(ctx->dest_image, column_index, row_index,
		color_to_int(clamped));
}

void	blur_row(t_gauss_ctx *ctx, int row_index)
{
	int	column;

	column = 0;
	while (column < ctx->source_image->width)
	{
		put_blurred_pixel(ctx, row_index, column, 1);
		column++;
	}
}

void	blur_column(t_gauss_ctx *ctx, int column_index)
{
	int	row;

	row = 0;
	while (row < ctx->source_image->height)
	{
		put_blurred_pixel(ctx, row, column_index, 0);
		row++;
	}
}
