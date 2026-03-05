/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_post_process_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:05:43 by eraad             #+#    #+#             */
/*   Updated: 2026/03/06 00:54:47 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_POST_PROCESS_BONUS_H
# define S_POST_PROCESS_BONUS_H

# include "structs/s_scene_bonus.h"

typedef struct s_gauss_ctx
{
	t_image		*source_image;
	t_image		*dest_image;
	int			kernel_half_size;
	t_real		*weights;
}				t_gauss_ctx;

typedef struct s_two_pass_ctx
{
	t_image		*source_image;
	t_image		*inter_image;
	t_image		*dest_image;
	int			kernel_half_size;
	t_real		*weights;
}				t_two_pass_ctx;

typedef struct s_w_result
{
	t_color		sum;
	t_real		total;
}				t_w_result;

typedef struct s_add_params
{
	t_gauss_ctx	*ctx;
	int			row_index;
	int			column_index;
	int			offset;
	int			is_horizontal;
}				t_add_params;

typedef struct s_sharp_ctx
{
	t_color		center;
	t_color		left;
	t_color		right;
	t_color		up;
	t_color		down;
	t_real		strength;
}				t_sharp_ctx;

#endif