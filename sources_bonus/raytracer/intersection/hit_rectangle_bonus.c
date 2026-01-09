/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_rectangle_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:53:23 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 13:20:05 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	set_rectangle_record(t_object *object, t_ray *world_ray,
		t_hit_record *record)
{
	record->hit_point = vec3_add(world_ray->origin,
			vec3_scale(world_ray->direction, record->t));
	record->color = object->color;
	record->object = object;
	if (record->need_details == FALSE)
		return ;
	record->normal = object->u_data.rectangle.normal;
	set_face_normal(record, world_ray, record->normal);
}

t_bool	hit_rectangle(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_ray	object_ray;
	t_real	t;
	t_real	x;
	t_real	z;

	object_ray = transform_ray(*world_ray, object->inverse);
	if (fabs(object_ray.direction.y) < EPSILON)
		return (FALSE);
	t = -object_ray.origin.y / object_ray.direction.y;
	if (t < world_ray->min || t > world_ray->max)
		return (FALSE);
	x = object_ray.origin.x + t * object_ray.direction.x;
	z = object_ray.origin.z + t * object_ray.direction.z;
	if (fabs(x) > 0.5 || fabs(z) > 0.5)
		return (FALSE);
	record->t = t;
	set_rectangle_record(object, world_ray, record);
	return (TRUE);
}
