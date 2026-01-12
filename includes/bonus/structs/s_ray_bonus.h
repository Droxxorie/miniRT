/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_ray_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:49:53 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 15:51:22 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_RAY_BONUS_H
# define S_RAY_BONUS_H

# include "s_math_bonus.h"

typedef struct s_object	t_object;

typedef struct s_ray
{
	t_point3			origin;
	t_vec3				direction;
	t_real				min;
	t_real				max;
}						t_ray;

typedef struct s_aabb
{
	t_point3			min;
	t_point3			max;
}						t_aabb;

typedef struct s_hit_record
{
	t_object			*object;
	t_point3			hit_point;
	t_vec3				normal;
	t_real				t;
	t_bool				front_face;
	t_color				color;
	t_bool				need_details;
}						t_hit_record;

typedef struct s_bvh_node
{
	t_aabb				box;
	struct s_bvh_node	*left_child;
	struct s_bvh_node	*right_child;
	t_object			*content;
	int					axis;
}						t_bvh_node;

#endif