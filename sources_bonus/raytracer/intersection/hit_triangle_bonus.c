/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_triangle_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:15:05 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 14:23:48 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	set_triangle_record(t_object *object, t_ray *world_ray,
		t_hit_record *record)
{
	record->hit_point = vec3_add(world_ray->origin,
			vec3_scale(world_ray->direction, record->t));
	record->color = object->color;
	record->object = object;
	if (record->need_details == FALSE)
		return ;
	record->normal = object->u_data.triangle.normal;
	set_face_normal(record, world_ray, record->normal);
}

//* Moeller-Trumbore intersection algorithm
t_bool	hit_triangle(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_triangle		*triangle;
	t_triangle_hit	vars;

	triangle = &object->u_data.triangle;
	vars.h = vec3_cross(world_ray->direction, triangle->edge2);
	vars.a = vec3_dot(triangle->edge1, vars.h);
	if (vars.a > -EPSILON && vars.a < EPSILON)
		return (FALSE);
	vars.f = 1.0 / vars.a;
	vars.s = vec3_sub(world_ray->origin, triangle->p1);
	vars.u = vars.f * vec3_dot(vars.s, vars.h);
	if (vars.u < 0.0 || vars.u > 1.0)
		return (FALSE);
	vars.q = vec3_cross(vars.s, triangle->edge1);
	vars.v = vars.f * vec3_dot(world_ray->direction, vars.q);
	if (vars.v < 0.0 || vars.u + vars.v > 1.0)
		return (FALSE);
	vars.t = vars.f * vec3_dot(triangle->edge2, vars.q);
	if (vars.t > world_ray->min && vars.t < world_ray->max)
	{
		record->t = vars.t;
		set_triangle_record(object, world_ray, record);
		return (TRUE);
	}
	return (FALSE);
}
