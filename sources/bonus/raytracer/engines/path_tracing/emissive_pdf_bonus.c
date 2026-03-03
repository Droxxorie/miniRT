/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emissive_pdf_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 00:00:00 by eraad             #+#    #+#             */
/*   Updated: 2026/03/03 15:33:33 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_real	emissive_area_simple(t_object *obj)
{
	t_real	r;

	if (obj->type == RECTANGLE)
		return (obj->u_data.rectangle.width * obj->u_data.rectangle.height);
	if (obj->type == SPHERE)
	{
		r = obj->u_data.sphere.radius;
		return (4.0 * PI * r * r);
	}
	if (obj->type == DISK)
	{
		r = obj->u_data.disk.radius;
		return (PI * r * r);
	}
	if (obj->type == TRIANGLE)
		return (0.5 * vec3_len(vec3_cross(obj->u_data.triangle.edge1,
					obj->u_data.triangle.edge2)));
	return (-1.0);
}

static t_real	emissive_area(t_object *obj)
{
	t_real	area;
	t_real	r;
	t_real	h;

	area = emissive_area_simple(obj);
	if (area >= 0.0)
		return (area);
	if (obj->type == CYLINDER)
		return (2.0 * PI * obj->u_data.cylinder.radius
			* obj->u_data.cylinder.height);
	if (obj->type == CONE)
	{
		r = obj->u_data.cone.radius;
		h = obj->u_data.cone.height;
		return (PI * r * sqrt(r * r + h * h));
	}
	if (obj->type == BOX)
		return (2.0 * (obj->u_data.box.width * obj->u_data.box.height
				+ obj->u_data.box.height * obj->u_data.box.depth
				+ obj->u_data.box.width * obj->u_data.box.depth));
	if (obj->type == TORUS)
		return (4.0 * PI * PI * obj->u_data.torus.major_radius
			* obj->u_data.torus.minor_radius);
	return (1.0);
}

t_real	compute_emissive_pdf(t_hit_record *rec, t_vec3 ray_dir)
{
	t_real	area;
	t_real	cos_light;

	area = emissive_area(rec->object);
	if (area < EPSILON)
		area = EPSILON;
	cos_light = fmax(vec3_dot(rec->normal, vec3_scale(ray_dir, -1.0)), 0.0);
	if (cos_light < 0.01)
		cos_light = 0.01;
	return ((rec->t * rec->t) / (area * cos_light + EPSILON));
}
