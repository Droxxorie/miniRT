/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_sharpen_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:00:00 by eraad             #+#    #+#             */
/*   Updated: 2026/03/06 00:55:28 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_color	compute_sharpened_pixel_color(t_sharp_ctx *ctx)
{
	t_color	sharpened_color;

	sharpened_color.r = ctx->center.r * (1.0 + 4.0 * ctx->strength)
		- (ctx->left.r + ctx->right.r + ctx->up.r + ctx->down.r)
		* ctx->strength;
	sharpened_color.g = ctx->center.g * (1.0 + 4.0 * ctx->strength)
		- (ctx->left.g + ctx->right.g + ctx->up.g + ctx->down.g)
		* ctx->strength;
	sharpened_color.b = ctx->center.b * (1.0 + 4.0 * ctx->strength)
		- (ctx->left.b + ctx->right.b + ctx->up.b + ctx->down.b)
		* ctx->strength;
	sharpened_color.r = ft_clamp(sharpened_color.r, 0.0, 1.0);
	sharpened_color.g = ft_clamp(sharpened_color.g, 0.0, 1.0);
	sharpened_color.b = ft_clamp(sharpened_color.b, 0.0, 1.0);
	return (sharpened_color);
}

static void	apply_sharpen_to_row(t_image *source_image, t_image *dest_image,
		int row_index, t_real strength)
{
	int			column;
	t_sharp_ctx	ctx;

	column = 0;
	while (column < source_image->width)
	{
		ctx.center = get_pixel_color(source_image, column, row_index);
		ctx.left = get_pixel_color(source_image, column - 1, row_index);
		ctx.right = get_pixel_color(source_image, column + 1, row_index);
		ctx.up = get_pixel_color(source_image, column, row_index - 1);
		ctx.down = get_pixel_color(source_image, column, row_index + 1);
		ctx.strength = strength;
		image_pixel_put(dest_image, column, row_index,
			color_to_int(compute_sharpened_pixel_color(&ctx)));
		column++;
	}
}

void	apply_filter_sharpen(t_image *src, t_image *dst, t_real strength)
{
	int	row_index;

	row_index = 0;
	while (row_index < src->height)
	{
		apply_sharpen_to_row(src, dst, row_index, strength);
		row_index++;
	}
}
