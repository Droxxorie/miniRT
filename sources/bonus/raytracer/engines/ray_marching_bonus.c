/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_marching_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 23:45:18 by eraad             #+#    #+#             */
/*   Updated: 2026/01/14 22:57:37 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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
	// else if (object->type == MENGER_SPONGE)
	// 	return (sdf_menger_sponge(p, object));
	else if (object->type == MANDELBULB)
		return (sdf_mandelbulb(p, object));
	else if (object->type == MANDELBOX)
		return (sdf_mandelbox(p, object));
	return (INFINITY);
}

static t_vec3	get_sdf_normal(t_point3 p, t_object *object)
{
	t_real	d;
	t_vec3	n;

	d = dispatch_sdf(p, object);
	n.x = dispatch_sdf((t_point3){p.x + EPSILON, p.y, p.z}, object) - d;
	n.y = dispatch_sdf((t_point3){p.x, p.y + EPSILON, p.z}, object) - d;
	n.z = dispatch_sdf((t_point3){p.x, p.y, p.z + EPSILON}, object) - d;
	return (vec3_normalize(n));
}

static	t_color	get_fractal_color(t_point3 point, t_object *object)
{
	if (object->type == MANDELBULB)
		return (get_mandelbulb_color(point, object));
	else if (object->type == MANDELBOX)
		return (get_mandelbox_color(point, object));
	// else if (object->type == MENGER_SPONGE)
	// 	return (object->color);
	return (object->color);
}

static t_bool	set_sdf_record(t_object *object, t_ray *world_ray,
		t_hit_record *record)
{
	t_point3	local_hit;
	t_vec3		local_normal;

	record->object = object;
	record->hit_point = ray_at(world_ray, record->t);
	local_hit = mat4_mult_point3(object->inverse, record->hit_point);
	local_normal = get_sdf_normal(local_hit, object);
	if (object->is_fractal == TRUE)
		record->color = get_fractal_color(local_hit, object);
	else
		record->color = object->color;
	if (world_ray->is_shadow_ray == TRUE)
		return (TRUE);
	record->normal = mat4_mult_vec3(object->transposed_inverse, local_normal);
	record->normal = vec3_normalize(record->normal);
	set_face_normal(record, world_ray, record->normal);
	return (TRUE);
}

t_bool	ray_march(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_ray_march_data	d;
	t_real				step_factor;
	t_real				threshold;
	int					steps;

	step_factor = 1.0;
	threshold = EPSILON;
	steps = MAX_SDF_STEPS;
	if (object->is_fractal == TRUE)
	{
		threshold = 0.0001;
		step_factor = .15;
		steps = 2000;
	}
	d.depth = world_ray->min;
	d.scale = object->sdf_scale;
	d.steps = 0;
	while (d.steps++ < steps)
	{
		d.world_p = ray_at(world_ray, d.depth);
		d.local_p = mat4_mult_point3(object->inverse, d.world_p);
		d.local_dist = dispatch_sdf(d.local_p, object);
		d.world_dist = d.local_dist * d.scale * step_factor;
		if (d.world_dist < threshold)
		{
			record->t = d.depth;
			return (set_sdf_record(object, world_ray, record));
		}
		d.depth += d.world_dist;
		if (d.depth > world_ray->max)
			return (FALSE);
	}
	return (FALSE);
}
