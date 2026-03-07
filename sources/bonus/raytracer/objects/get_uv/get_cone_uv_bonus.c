/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cone_uv_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 21:18:33 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 21:19:52 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	get_cone_uv(t_point3 p, t_cylinder_element type, t_real *u,
		t_real *v)
{
	t_real	phi;

	if (type == BODY)
	{
		phi = atan2f(-p.z, p.x) + PI;
		*u = phi * INV_TWO_PI;
		*v = p.y;
	}
	else
	{
		*u = (p.x + 1.0) * 0.5;
		*v = (p.z + 1.0) * 0.5;
	}
}
