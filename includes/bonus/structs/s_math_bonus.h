/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_math_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:48:43 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 21:55:07 by eraad            ###   ########.fr       */
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
	double		coeffs[4];
	double		roots[3];
	int			roots_count;
	double		a;
	double		sq_a;
	double		b;
	double		c;
	double		p;
	double		cube_p;
	double		q;
	double		delta;
	double		sqrt_delta;
	double		phi;
	double		u;
	double		v;
}				t_cubic;

typedef struct s_quartic
{
	double		coeffs[5];
	double		roots[4];
	int			roots_count;
	double		a;
	double		sq_a;
	double		b;
	double		c;
	double		d;
	double		y;
	double		r_var;
	double		e;
	double		f;
	t_cubic		cubic_vars;
}				t_quartic;

typedef struct s_color
{
	t_real		r;
	t_real		g;
	t_real		b;
}				t_color;

#endif