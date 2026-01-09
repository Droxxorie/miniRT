/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_disk_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:09:48 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 13:40:54 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	set_disk_record(t_object *object, t_ray *world_ray,
		t_hit_record *record)
{
	record->hit_point = vec3_add(world_ray->origin,
			vec3_scale(world_ray->direction, record->t));
	record->color = object->color;
	record->object = object;
	if (record->need_details == FALSE)
		return ;
	record->normal = object->u_data.disk.normal;
	set_face_normal(record, world_ray, record->normal);
}

t_bool	hit_disk(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_ray	object_ray;
	t_real	t;
	t_real	x;
	t_real	z;
	t_real	r_squared;

	object_ray = transform_ray(*world_ray, object->inverse);
	if (fabs(object_ray.direction.y) < EPSILON)
		return (FALSE);
	t = -object_ray.origin.y / object_ray.direction.y;
	if (t < world_ray->min || t > world_ray->max)
		return (FALSE);
	x = object_ray.origin.x + t * object_ray.direction.x;
	z = object_ray.origin.z + t * object_ray.direction.z;
	r_squared = x * x + z * z;
	if (r_squared > 1.0)
		return (FALSE);
	record->t = t;
	set_disk_record(object, world_ray, record);
	return (TRUE);
}
