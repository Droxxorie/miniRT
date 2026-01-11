/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus_bounds_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:29:46 by eraad             #+#    #+#             */
/*   Updated: 2026/01/11 20:54:13 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_aabb	compute_torus_bounds(t_object *obj)
{
	t_aabb	local;
	t_torus	*torus;
	t_real	total_radius;

	torus = &obj->u_data.torus;
	total_radius = torus->major_radius + torus->minor_radius;
	local.min = (t_point3){-total_radius, -torus->minor_radius, -total_radius};
	local.max = (t_point3){total_radius, torus->minor_radius, total_radius};
	return (local);
}
