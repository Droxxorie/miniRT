/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:18:51 by eraad             #+#    #+#             */
/*   Updated: 2026/03/06 00:44:10 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POST_PROCESS_BONUS_H
# define POST_PROCESS_BONUS_H

# include "structs/s_post_process_bonus.h"

void		apply_post_filters(t_scene *scene);
void		apply_filter_sobel(t_image *src, t_image *dst);
void		apply_filter_bnw(t_image *img);
void		apply_filter_gaussian(t_image *src, t_image *dst, t_real radius);
void		apply_filter_sepia(t_image *img);
void		apply_filter_sharpen(t_image *src, t_image *dst, t_real strength);
void		apply_filter_contrast(t_image *img, t_real factor);
void		apply_filter_saturation(t_image *img, t_real factor);
t_color		gamma_correction(t_color color);
t_color		aces_tone_mapping(t_color hdr);
void		build_spiral_order(t_scene *s);
void		blur_row(t_gauss_ctx *ctx, int row_index);
void		blur_column(t_gauss_ctx *ctx, int column_index);
t_w_result	get_weighted_sum_horizontal(t_gauss_ctx *ctx, int row_index,
				int column_index);
t_w_result	get_weighted_sum_vertical(t_gauss_ctx *ctx, int column_index,
				int row_index);

#endif