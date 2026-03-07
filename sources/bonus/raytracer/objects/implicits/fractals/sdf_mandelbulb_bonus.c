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

static void	iterate_mandelbulb(double *z, double *r, double *dr, double power)
{
	double	theta;
	double	phi;
	double	zr;

	theta = acos(z[1] / *r);
	phi = atan2(z[2], z[0]);
	if (dr)
		*dr = pow(*r, power - 1.0) * power * *dr + 1.0;
	theta = theta * power;
	phi = phi * power;
	zr = pow(*r, power);
	z[0] = zr * sin(theta) * cos(phi);
	z[1] = zr * cos(theta);
	z[2] = zr * sin(theta) * sin(phi);
}

static t_color	mandelbulb_palette(double min_trap, t_object *object)
{
	return (cosine_palette((t_real)log(min_trap + EPSILON),
			(t_color[4]){object->color, (t_color){0.5f, 0.5f, 0.5f},
		(t_color){2.0f, 2.0f, 2.0f}, (t_color){0.00f, 0.15f, 0.30f}}));
}

t_color	get_mandelbulb_color(t_point3 p, t_object *object)
{
	double	z[3];
	double	r;
	double	min_trap;
	int		i;

	z[0] = p.x;
	z[1] = p.y;
	z[2] = p.z;
	min_trap = 1e20;
	i = -1;
	while (++i < 10)
	{
		r = sqrt(z[0] * z[0] + z[1] * z[1] + z[2] * z[2]);
		if (r > 2.0)
			break ;
		min_trap = fmin(get_trap_distance((t_vec3){(float)z[0], (float)z[1],
					(float)z[2]}, 2), min_trap);
		iterate_mandelbulb(z, &r, NULL,
			(double)object->u_data.mandelbulb.power);
		z[0] += p.x;
		z[1] += p.y;
		z[2] += p.z;
	}
	return (mandelbulb_palette(min_trap, object));
}

t_real	sdf_mandelbulb(t_point3 p, t_object *object)
{
	double	z[3];
	double	r;
	double	dr;
	int		i;

	if (vec3_len(p) > 1.5f)
		return (vec3_len(p) - 1.2f);
	dr = 1.0;
	z[0] = p.x;
	z[1] = p.y;
	z[2] = p.z;
	i = -1;
	while (++i < 20)
	{
		r = sqrt(z[0] * z[0] + z[1] * z[1] + z[2] * z[2]);
		if (r > 2.0)
			break ;
		iterate_mandelbulb(z, &r, &dr, (double)object->u_data.mandelbulb.power);
		z[0] += p.x;
		z[1] += p.y;
		z[2] += p.z;
	}
	return ((t_real)(0.5 * log(r) * r / dr));
}
