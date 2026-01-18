/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_math_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:48:43 by eraad             #+#    #+#             */
/*   Updated: 2026/01/16 20:05:25 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_MATH_BONUS_H
# define S_MATH_BONUS_H

# include "s_base_bonus.h"

typedef struct s_vec2
{
	t_real		x;
	t_real		y;
}				t_vec2;

typedef struct s_vec3
{
	t_real		x;
	t_real		y;
	t_real		z;
}				t_vec3;

typedef t_vec3	t_point3;

typedef struct s_vec4
{
	t_real		x;
	t_real		y;
	t_real		z;
	t_real		w;
}				t_vec4;


typedef struct s_mat4
{
	t_real		m[4][4];
}				t_mat4;

typedef struct s_quadratic
{
	t_real		a;
	t_real		half_b;
	t_real		c;
	t_real		root1;
	t_real		root2;
}				t_quadratic;

typedef struct s_cubic
{
	t_real		coeffs[4];
	t_real		roots[3];
	int			roots_count;
	t_real		a;
	t_real		sq_a;
	t_real		b;
	t_real		c;
	t_real		p;
	t_real		cube_p;
	t_real		q;
	t_real		delta;
	t_real		sqrt_delta;
	t_real		phi;
	t_real		u;
	t_real		v;
}				t_cubic;

typedef struct s_quartic
{
	t_real		coeffs[5];
	t_real		roots[4];
	int			roots_count;
	t_real		a;
	t_real		sq_a;
	t_real		b;
	t_real		c;
	t_real		d;
	t_real		y;
	t_real		r_var;
	t_real		e;
	t_real		f;
	t_cubic		cubic_vars;
}				t_quartic;

typedef struct s_color
{
	t_real		r;
	t_real		g;
	t_real		b;
}				t_color;

#endif