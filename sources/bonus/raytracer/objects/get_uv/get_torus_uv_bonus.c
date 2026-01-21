/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_torus_uv_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 21:19:34 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 21:28:33 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	get_torus_uv(t_point3 p, t_torus *torus, t_real *u, t_real *v)
{
	t_real	phi;
	t_real	theta;
	t_real	xz_dist;

	phi = atan2(-p.z, p.x) + PI;
	*u = phi * INV_TWO_PI;
	xz_dist = sqrt(p.x * p.x + p.z * p.z);
	theta = atan2(p.y, xz_dist - torus->major_radius) + PI;
	*v = theta * INV_TWO_PI;
}
