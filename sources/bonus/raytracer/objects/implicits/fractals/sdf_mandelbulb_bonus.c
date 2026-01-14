/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_mandelbulb_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:28:21 by eraad             #+#    #+#             */
/*   Updated: 2026/01/14 23:43:51 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	iterate_mandelbulb(t_vec3 *z, t_real *r, t_real *dr, t_real power)
{
	t_real	theta;
	t_real	phi;
	t_real	zr;

	theta = acos(z->y / *r);
	phi = atan2(z->z, z->x);
	if (dr)
		*dr = pow(*r, power - 1.0) * power * *dr + 1.0;
	theta = theta * power;
	phi = phi * power;
	zr = pow(*r, power);
	z->x = zr * sin(theta) * cos(phi);
	z->y = zr * cos(theta);
	z->z = zr * sin(theta) * sin(phi);
}

t_color	get_mandelbulb_color(t_point3 p, t_object *object)
{
	t_vec3	z;
	t_real	r;
	t_real	min_trap;
	t_real	current_dist;
	int		i;

	z = p;
	r = 0.0;
	min_trap = 1e20;
	i = -1;
	while (++i < 10)
	{
		r = vec3_len(z);
		if (r > 2.0)
			break ;
		current_dist = get_trap_distance(z, 2);
		if (current_dist < min_trap)
			min_trap = current_dist;
		iterate_mandelbulb(&z, &r, NULL, object->u_data.mandelbulb.power);
		z = vec3_add(z, p);
	}
	return (cosine_palette(log(min_trap + EPSILON), (t_color[4]){object->color,
			(t_color){0.5, 0.5, 0.5}, (t_color){2.0, 2.0, 2.0}, (t_color){0.00,
			0.15, 0.30}}));
}

t_real	sdf_mandelbulb(t_point3 p, t_object *object)
{
	t_vec3	z;
	t_real	r;
	t_real	dr;
	int		i;
	t_real	dist_origin;

	dist_origin = vec3_len(p);
	if (dist_origin > 1.5)
		return (dist_origin - 1.2);
	dr = 1.0;
	r = 0.0;
	z = p;
	i = -1;
	while (++i < 20)
	{
		r = vec3_len(z);
		if (r > 2.0)
			break ;
		iterate_mandelbulb(&z, &r, &dr, object->u_data.mandelbulb.power);
		z = vec3_add(z, p);
	}
	return (0.5 * log(r) * r / dr);
}
