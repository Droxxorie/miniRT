/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:13:24 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 15:06:49 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include <math.h>

# define EPSILON 1e-8
// # define INFINITY 1.0e30f
# define COLOR_SIZE 8
# define PI 3.14159265359
# define TWO_PI 6.28318530718
# define INV_255 0.00392156862

# define U_X 0
# define U_Y 1
# define U_Z 2

typedef double	t_real;
typedef t_vec3	t_point3;

typedef struct s_vec2
{
	t_real		u;
	t_real		v;
}				t_vec2;

typedef struct s_vec3
{
	t_real		x;
	t_real		y;
	t_real		z;
}				t_vec3;

typedef enum e_mat_axis
{
	AXIS_RIGHT,   // X axis
	AXIS_UP,      // Y axis
	AXIS_FORWARD, // Z axis
	AXIS_ORIGIN   // Translation
}				t_mat_axis;

typedef struct s_mat4
{
	t_real		m[4][4];
}				t_mat4;

//* Vector operations */
t_vec3			vec3_add(const t_vec3 u, const t_vec3 v);
t_vec3			vec3_add_scalar(const t_vec3 v, const t_real k);
t_vec3			vec3_scale(const t_vec3 v, const t_real k);
t_vec3			vec3_prod(const t_vec3 u, const t_vec3 v);
t_real			vec3_len_squared(const t_vec3 v);
t_real			vec3_len(const t_vec3 v);
t_vec3			vec3_normalize(const t_vec3 v);
t_vec3			vec3_cross(const t_vec3 u, const t_vec3 v);
t_real			vec3_dot(const t_vec3 u, const t_vec3 v);
t_vec3			vec3_sub(const t_vec3 u, const t_vec3 v);
t_vec3			vec3_sub_scalar(const t_vec3 v, const t_real k);

//* Color operations */
t_color			color_add(const t_color c1, const t_color c2);
t_color			color_add_scalar(const t_color color, const t_real k);
t_color			color_scale(const t_color color, const t_real k);
t_color			color_prod(const t_color c1, const t_color c2);

//* Matrix operations */
#endif