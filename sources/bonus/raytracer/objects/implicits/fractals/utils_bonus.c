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

t_color	lerp_color(t_color c1, t_color c2, double t)
{
	t_color	result;

	if (t < 0.0)
		t = 0.0;
	if (t > 1.0)
		t = 1.0;
	result.r = c1.r + (c2.r - c1.r) * t;
	result.g = c1.g + (c2.g - c1.g) * t;
	result.b = c1.b + (c2.b - c1.b) * t;
	return (result);
}

//* Trap Distance Functions
//* 0: Plane Trap
//* 1: Spherical Shell
//* 2: Point Trap
//* default: y-axis
t_real	get_trap_distance(t_vec3 z, int mode)
{
	t_real	len;

	len = vec3_len(z);
	if (mode == 0)
		return (fabs(z.x));
	else if (mode == 1)
		return (fabs(len - 1.0));
	else if (mode == 2)
		return (len);
	return (fabs(z.y));
}

//* Palette procédurale (Inigo Quilez)
//* t : le facteur (entre 0 et ce que tu veux)
//* a : luminosité moyenne
//* b : contraste
//* c : fréquence
//* d : phase (décalage des couleurs)
t_color	cosine_palette(t_real t, t_color *params)
{
	t_color	a;
	t_color	b;
	t_color	c;
	t_color	d;
	t_color	col;

	a = params[0];
	b = params[1];
	c = params[2];
	d = params[3];
	col.r = a.r + b.r * cos(TWO_PI * (c.r * t + d.r));
	col.g = a.g + b.g * cos(TWO_PI * (c.g * t + d.g));
	col.b = a.b + b.b * cos(TWO_PI * (c.b * t + d.b));
	col.r = ft_clamp(col.r, 0.0, 1.0);
	col.g = ft_clamp(col.g, 0.0, 1.0);
	col.b = ft_clamp(col.b, 0.0, 1.0);
	return (col);
}
