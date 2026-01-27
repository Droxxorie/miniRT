/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tonemapping_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 13:59:14 by eraad             #+#    #+#             */
/*   Updated: 2026/01/24 14:02:19 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_real	aces_curve(t_real x)
{
	t_real	a;
	t_real	b;
	t_real	c;
	t_real	d;
	t_real	e;

	a = 2.51;
	b = 0.03;
	c = 2.43;
	d = 0.59;
	e = 0.14;
	return (ft_clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0));
}

t_color	aces_tone_mapping(t_color hdr)
{
	t_color	ldr;

	ldr.r = aces_curve(hdr.r);
	ldr.g = aces_curve(hdr.g);
	ldr.b = aces_curve(hdr.b);
	return (ldr);
}

t_color	gamma_correction(t_color color)
{
	t_real	inv_gamma;

	inv_gamma = 1.0 / 2.2;
	color.r = pow(color.r, inv_gamma);
	color.g = pow(color.g, inv_gamma);
	color.b = pow(color.b, inv_gamma);
	return (color);
}
