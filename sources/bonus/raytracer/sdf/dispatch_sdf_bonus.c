/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_sdf_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 22:06:06 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 16:26:16 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	dispatch_sdf(t_point3 p, t_object *object)
{
	if (object->type == CONE)
		return (sdf_cone(p));
	if (object->type == CYLINDER)
		return (sdf_cylinder(p));
	if (object->type == SPHERE)
		return (sdf_sphere(p));
	if (object->type == BOX)
		return (sdf_box(p));
	if (object->type == TORUS)
		return (sdf_torus(p, object->u_data.torus.major_radius,
				object->u_data.torus.minor_radius));
	if (object->type == DISK)
		return (sdf_disk(p));
	if (object->type == RECTANGLE)
		return (sdf_rectangle(p));
	if (object->type == TRIANGLE)
		return (sdf_triangle(p, object));
	return (INFINITY);
}
