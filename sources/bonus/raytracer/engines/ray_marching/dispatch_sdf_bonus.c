/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_sdf_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:23:02 by eraad             #+#    #+#             */
/*   Updated: 2026/01/15 18:39:34 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_color	get_fractal_color(t_point3 point, t_object *object)
{
	if (object->type == MANDELBULB)
		return (get_mandelbulb_color(point, object));
	else if (object->type == MANDELBOX)
		return (get_mandelbox_color(point, object));
	else if (object->type == MENGER_SPONGE)
		return (get_menger_sponge_color(point, object));
	return (object->color);
}

t_real	dispatch_sdf(t_point3 p, t_object *object)
{
	if (object->type == CONE)
		return (sdf_cone(p));
	else if (object->type == CYLINDER)
		return (sdf_cylinder(p));
	else if (object->type == SPHERE)
		return (sdf_sphere(p));
	else if (object->type == BOX)
		return (sdf_box(p));
	else if (object->type == TORUS)
		return (sdf_torus(p, object->u_data.torus.major_radius,
				object->u_data.torus.minor_radius));
	else if (object->type == DISK)
		return (sdf_disk(p));
	else if (object->type == RECTANGLE)
		return (sdf_rectangle(p));
	else if (object->type == TRIANGLE)
		return (sdf_triangle(p, object));
	else if (object->type == MENGER_SPONGE)
		return (sdf_menger_sponge(p, object));
	else if (object->type == MANDELBULB)
		return (sdf_mandelbulb(p, object));
	else if (object->type == MANDELBOX)
		return (sdf_mandelbox(p, object));
	printf("Error: Unknown object type in dispatch_sdf_bonus.c\n");
	return (INFINITY);
}
