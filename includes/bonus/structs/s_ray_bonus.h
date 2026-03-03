/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_ray_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:49:53 by eraad             #+#    #+#             */
/*   Updated: 2026/01/25 18:55:05 by eraad            ###   ########.fr       */
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
	t_color				color;
	t_color				albedo;
	t_color				f0;
	t_real				t;
	t_real				u;
	t_real				v;
	t_real				roughness;
	t_real				metallic;
	t_bool				front_face;
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
	t_real				scale;
	t_real				threshold;
	t_real				step_factor;
	int					steps;
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

typedef struct s_path_info
{
	t_bvh_node		*bvh_root;
	t_vec3			next_dir;
	t_color			final;
	t_color			thru;
	t_real			last_pdf;
	t_real			pdf;
	t_real			bsdf_weight;
	unsigned int	seed;
	int				depth;
	t_bool			specular_bounce;
	t_bool			front_face;
}					t_path_info;

typedef struct s_light_sample_vars
{
	t_vec3		light_dir;
	t_vec3		light_pos;
	t_real		dist;
	t_real		weight;
	t_color		f_r;
	t_color		transmittance;
}				t_light_sample_vars;

#endif