/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_sdf_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:23:02 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 17:25:22 by eraad            ###   ########.fr       */
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
	else if (object->type == JULIA_SET)
		return (get_julia_set_color(point, object));
	return (object->color);
}

static t_real	dispatch_fractals(t_point3 p, t_object *object)
{
	if (object->type == MANDELBULB)
		return (sdf_mandelbulb(p, object));
	else if (object->type == MANDELBOX)
		return (sdf_mandelbox(p, object));
	else if (object->type == MENGER_SPONGE)
		return (sdf_menger_sponge(p, object));
	else if (object->type == JULIA_SET)
		return (sdf_julia_set(p, object));
	return (INFINITY);
}

t_real	dispatch_sdf(t_point3 p, t_object *object)
{
	t_point3	local_p;
	t_real		dist;

	local_p = mat4_mult_point3(object->inverse, p);
	if (object->type == CYLINDER)
		dist = sdf_cylinder(local_p);
	else if (object->type == CONE)
		dist = sdf_cone(local_p);
	else if (object->type == SPHERE)
		dist = sdf_sphere(local_p);
	else if (object->type == BOX)
		dist = sdf_box(local_p);
	else if (object->type == TORUS)
		dist = sdf_torus(local_p, object->u_data.torus.major_radius,
				object->u_data.torus.minor_radius);
	else if (object->type == DISK)
		dist = sdf_disk(local_p);
	else if (object->type == RECTANGLE)
		dist = sdf_rectangle(local_p);
	else if (object->type == TRIANGLE)
		dist = sdf_triangle(local_p, object);
	else
		dist = dispatch_fractals(local_p, object);
	return (dist);
}
