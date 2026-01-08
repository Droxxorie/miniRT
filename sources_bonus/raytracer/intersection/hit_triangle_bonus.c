/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_triangle_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:15:05 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 22:24:22 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	set_triangle_record(t_object *object, t_ray *world_ray,
		t_ray *object_ray, t_hit_record *record)
{
	t_vec3	local_normal;

	record->hit_point = vec3_add(world_ray->origin,
			vec3_scale(world_ray->direction, record->t));
	record->color = object->color;
	record->object = object;
	if (record->need_details == FALSE)
		return ;
	local_normal = (t_vec3){0.0, 0.0, 1.0};
	if (object_ray->direction.z > 0.0)
		local_normal = (t_vec3){0.0, 0.0, -1.0};
	record->normal = vec3_normalize(mat4_mult_vec3(object->transposed_inverse,
				local_normal));
	set_face_normal(record, world_ray, record->normal);
}

t_bool	hit_triangle(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_ray	object_ray;
	t_real	t;
	t_real	u;
	t_real	v;

	object_ray = transform_ray(*world_ray, object->inverse);
	if (fabs(object_ray.direction.z) < EPSILON)
		return (FALSE);
	t = -object_ray.origin.z / object_ray.direction.z;
	if (t < object_ray.min || t > object_ray.max)
		return (FALSE);
	u = object_ray.origin.x + t * object_ray.direction.x;
	v = object_ray.origin.y + t * object_ray.direction.y;
	if (u < 0.0 || v < 0.0 || (u + v) > 1.0)
		return (FALSE);
	record->t = t;
	set_triangle_record(object, world_ray, &object_ray, record);
	return (TRUE);
}
