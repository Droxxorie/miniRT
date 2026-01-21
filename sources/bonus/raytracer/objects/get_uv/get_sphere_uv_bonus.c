/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sphere_uv_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 21:19:13 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 22:41:18 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	get_sphere_uv(t_point3 p, t_real *u, t_real *v)
{
	t_real	theta;
	t_real	phi;

	theta = acos(-p.y);
	phi = atan2(-p.z, p.x) + PI;
	*u = phi * INV_TWO_PI;
	*v = theta * INV_PI;
}
