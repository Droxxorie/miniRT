/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_cone_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 23:24:35 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 15:23:48 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	sdf_cone(t_point3 p)
{
	t_real	q;
	t_real	d_side;
	t_real	d_cap;

	q = hypot(p.x, p.z);
	d_side = (q - (1.0 - p.y)) * INV_SQRT_2;
	d_cap = fmaxf(-p.y, p.y - 1.0);
	return (fmaxf(d_side, d_cap));
}
