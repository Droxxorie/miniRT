/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_gaussian_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:00:00 by eraad             #+#    #+#             */
/*   Updated: 2026/03/06 00:47:03 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	normalize_weights(t_real *weights, int half_size)
{
	int		index;
	t_real	sum;

	sum = 0;
	index = -half_size;
	while (index <= half_size)
	{
		sum += weights[index + half_size];
		index++;
	}
	index = 0;
	while (index < 2 * half_size + 1)
		weights[index++] /= sum;
}

static t_real	*build_kernel_weights(t_real radius, int *out_half_size)
{
	int		half_size;
	t_real	sigma;
	t_real	*weights;
	int		index;

	*out_half_size = (int)radius;
	if (*out_half_size < 1)
		*out_half_size = 1;
	weights = ft_calloc(2 * *out_half_size + 1, sizeof(t_real));
	if (!weights)
		return (NULL);
	sigma = radius / 2.0;
	if (sigma < 0.5)
		sigma = 0.5;
	half_size = *out_half_size;
	index = -half_size;
	while (index <= half_size)
	{
		weights[index + half_size] = expf(-(index * index) / (2.0 * sigma
					* sigma));
		index++;
	}
	normalize_weights(weights, half_size);
	return (weights);
}

static void	apply_two_pass(t_two_pass_ctx *tp)
{
	t_gauss_ctx	ctx;
	int			row_index;
	int			column_index;

	ctx.source_image = tp->source_image;
	ctx.dest_image = tp->inter_image;
	ctx.kernel_half_size = tp->kernel_half_size;
	ctx.weights = tp->weights;
	row_index = 0;
	while (row_index < tp->source_image->height)
	{
		blur_row(&ctx, row_index);
		row_index++;
	}
	ctx.source_image = tp->inter_image;
	ctx.dest_image = tp->dest_image;
	column_index = 0;
	while (column_index < tp->inter_image->width)
	{
		blur_column(&ctx, column_index);
		column_index++;
	}
}

void	apply_filter_gaussian(t_image *src, t_image *dst, t_real radius)
{
	int				kernel_half_size;
	t_real			*weights;
	char			*temp_buffer;
	t_image			inter_image;
	t_two_pass_ctx	tp_ctx;

	weights = build_kernel_weights(radius, &kernel_half_size);
	if (!weights)
		return ;
	temp_buffer = ft_calloc((size_t)src->height, (size_t)src->line_len);
	if (!temp_buffer)
		return (free(weights));
	inter_image = (t_image){.addr = temp_buffer, .line_len = src->line_len,
		.bpp = src->bpp, .width = src->width, .height = src->height};
	tp_ctx.source_image = src;
	tp_ctx.inter_image = &inter_image;
	tp_ctx.dest_image = dst;
	tp_ctx.kernel_half_size = kernel_half_size;
	tp_ctx.weights = weights;
	apply_two_pass(&tp_ctx);
	free(temp_buffer);
	free(weights);
}
