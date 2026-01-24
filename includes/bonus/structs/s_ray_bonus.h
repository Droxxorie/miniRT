/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_ray_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:49:53 by eraad             #+#    #+#             */
/*   Updated: 2026/01/24 13:09:45 by eraad            ###   ########.fr       */
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
	t_bool				is_shadow_ray;
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
	t_real				u;
	t_real				v;
}						t_hit_record;

typedef struct s_bvh_node
{
	t_aabb				box;
	struct s_bvh_node	*left_child;
	struct s_bvh_node	*right_child;
	t_object			*content;
	int					axis;
}						t_bvh_node;

typedef struct s_ray_march_data
{
	t_point3			world_p;
	t_point3			local_p;
	t_real				depth;
	t_real				local_dist;
	t_real				world_dist;
	int					steps;
	t_real				scale;
	t_real				threshold;
	t_real				step_factor;
	int					max_steps;
}						t_ray_march_data;

typedef struct s_cook_torrance_vars
{
	t_vec3				v;
	t_vec3				n;
	t_vec3				l;
	t_vec3				h;
	t_real				n_dot_l;
	t_real				n_dot_v;
	t_real				roughness;
	t_real				metallic;
	t_color				f0;
	t_color				albedo;
	int					depth;
}						t_cook_torrance_vars;

#endif