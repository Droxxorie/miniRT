/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 18:39:17 by eraad             #+#    #+#             */
/*   Updated: 2026/01/14 23:42:19 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_color	get_base_palette(t_real n)
{
	t_color	color;
	t_real	t;

	t = log2f(n) * 0.9f + 3.5f;
	color.r = 0.5f + 0.5f * cosf(t + 0.0f);
	color.g = 0.5f + 0.5f * cosf(t + 0.6f);
	color.b = 0.5f + 0.5f * cosf(t + 1.0f);
	return (color);
}

static void	julia_set_loop(t_julia_vars *v, double *z, t_vec4 c, t_bool der)
{
	double	sq[4];

	if (der)
	{
		sq[0] = z[0] * z[0] - z[1] * z[1] - z[2] * z[2] - z[3] * z[3];
		sq[1] = 2.0 * z[0] * z[1];
		sq[2] = 2.0 * z[0] * z[2];
		sq[3] = 2.0 * z[0] * z[3];
		v->dz *= 9.0 * (sq[0] * sq[0] + sq[1] * sq[1] + sq[2] * sq[2]
				+ sq[3] * sq[3]);
	}
	v->z = vec4_add(q_cube((t_vec4){(float)z[0], (float)z[1],
				(float)z[2], (float)z[3]}), c);
	z[0] = v->z.x;
	z[1] = v->z.y;
	z[2] = v->z.z;
	z[3] = v->z.w;
	v->magnitude_sq = z[0] * z[0] + z[1] * z[1] + z[2] * z[2] + z[3] * z[3];
	v->trap_d = fmin(v->trap_d, sqrt((z[0] - 0.45) * (z[0] - 0.45)
				+ (z[2] - 0.55) * (z[2] - 0.55)) - 0.1);
}

static t_julia_vars	julia_set_iters(double *z, t_vec4 c, int max_steps,
	t_bool derivate)
{
	t_julia_vars	v;
	int				i;

	v.dz = 1.0;
	v.trap_d = 1e10;
	v.n = 0.0;
	i = -1;
	while (++i < max_steps)
	{
		julia_set_loop(&v, z, c, derivate);
		if (v.magnitude_sq > 256.0)
			break ;
		v.n += 1.0;
	}
	return (v);
}

t_color	get_julia_set_color(t_point3 p, t_object *object)
{
	t_color			col;
	t_vec4			c;
	double			z[4];
	t_julia_vars	v;

	c = object->u_data.julia_set.c_constant;
	if (object->u_data.julia_set.preset == TRUE)
		c = (t_vec4){-0.090909f, 0.272727f, 0.681818f, -0.272727f};
	z[0] = (double)p.x;
	z[1] = (double)p.y;
	z[2] = (double)p.z;
	z[3] = 0.0;
	v = julia_set_iters(z, c, 300, FALSE);
	col = get_base_palette((t_real)v.n);
	if (p.y > 0.0f)
		col = color_mix(col, (t_color){1.0f, 1.0f, 1.0f}, 0.2f);
	return (apply_shading(col, (t_real)v.n));
}

t_real	sdf_julia_set(t_point3 p, t_object *object)
{
	double			dist;
	t_vec4			c;
	double			z[4];
	t_julia_vars	v;

	c = object->u_data.julia_set.c_constant;
	if (object->u_data.julia_set.preset == TRUE)
		c = (t_vec4){-0.090909f, 0.272727f, 0.681818f, -0.272727f};
	z[0] = (double)p.x;
	z[1] = (double)p.y;
	z[2] = (double)p.z;
	z[3] = 0.0;
	v = julia_set_iters(z, c, 200, TRUE);
	dist = 0.25 * log(v.magnitude_sq) * sqrt(v.magnitude_sq / v.dz);
	if (object->u_data.julia_set.orbital_trap)
		dist = fmin(dist, v.trap_d);
	if (object->u_data.julia_set.cut)
		dist = fmax(dist, (double)p.y - 0.1);
	return ((t_real)fmin(dist, 4.0));
}
