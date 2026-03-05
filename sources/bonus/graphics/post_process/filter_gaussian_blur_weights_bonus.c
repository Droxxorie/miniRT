/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_gaussian_blur_weights_bonus.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:00:00 by eraad             #+#    #+#             */
/*   Updated: 2026/03/06 00:43:30 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	add_sample_to_weighted_sum(t_add_params *params, t_color *sum,
		t_real *total)
{
	t_color	sample;
	t_real	weight;
	int		k;

	k = params->ctx->kernel_half_size;
	weight = params->ctx->weights[params->offset + k];
	if (params->is_horizontal)
		sample = get_pixel_color(params->ctx->source_image, params->column_index
				+ params->offset, params->row_index);
	else
		sample = get_pixel_color(params->ctx->source_image,
				params->column_index, params->row_index + params->offset);
	sum->r += sample.r * weight;
	sum->g += sample.g * weight;
	sum->b += sample.b * weight;
	*total += weight;
}

t_w_result	get_weighted_sum_horizontal(t_gauss_ctx *ctx, int row_index,
		int column)
{
	t_add_params	params;
	int				offset_x;
	t_color			weighted_sum;
	t_real			weight_total;

	weighted_sum = (t_color){0, 0, 0};
	weight_total = 0;
	params.ctx = ctx;
	params.row_index = row_index;
	params.column_index = column;
	params.is_horizontal = 1;
	offset_x = -ctx->kernel_half_size;
	while (offset_x <= ctx->kernel_half_size)
	{
		if (column + offset_x >= 0 && column
			+ offset_x < ctx->source_image->width)
		{
			params.offset = offset_x;
			add_sample_to_weighted_sum(&params, &weighted_sum, &weight_total);
		}
		offset_x++;
	}
	return ((t_w_result){weighted_sum, weight_total});
}

t_w_result	get_weighted_sum_vertical(t_gauss_ctx *ctx, int column_index,
		int row)
{
	t_add_params	params;
	int				offset_y;
	t_color			weighted_sum;
	t_real			weight_total;

	weighted_sum = (t_color){0, 0, 0};
	weight_total = 0;
	params.ctx = ctx;
	params.row_index = row;
	params.column_index = column_index;
	params.is_horizontal = 0;
	offset_y = -ctx->kernel_half_size;
	while (offset_y <= ctx->kernel_half_size)
	{
		if (row + offset_y >= 0 && row + offset_y < ctx->source_image->height)
		{
			params.offset = offset_y;
			add_sample_to_weighted_sum(&params, &weighted_sum, &weight_total);
		}
		offset_y++;
	}
	return ((t_w_result){weighted_sum, weight_total});
}
