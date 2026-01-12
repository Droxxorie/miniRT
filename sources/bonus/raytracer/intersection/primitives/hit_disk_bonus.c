/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_disk_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:09:48 by eraad             #+#    #+#             */
/*   Updated: 2026/01/11 23:59:09 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	set_disk_record(t_object *object, t_ray *world_ray,
		t_ray *local_ray, t_hit_record *record)
{
	t_vec3	local_normal;

	record->hit_point = ray_at(world_ray, record->t);
	record->color = object->color;
	record->object = object;
	if (record->need_details == FALSE)
		return ;
	if (local_ray->origin.y > 0)
		local_normal = (t_vec3){0, 1, 0};
	else
		local_normal = (t_vec3){0, -1, 0};
	record->normal = mat4_mult_vec3(object->transposed_inverse, local_normal);
	record->normal = vec3_normalize(record->normal);
	set_face_normal(record, world_ray, record->normal);
}

t_bool	hit_disk(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_ray	local_ray;
	t_real	t;
	t_real	x;
	t_real	z;
	t_real	r_squared;

	local_ray = transform_ray(*world_ray, object->inverse);
	if (local_ray.direction.y > EPSILON)
		return (FALSE);
	if (fabs(local_ray.direction.y) < EPSILON)
		return (FALSE);
	t = -local_ray.origin.y / local_ray.direction.y;
	if (t < world_ray->min || t > world_ray->max)
		return (FALSE);
	x = local_ray.origin.x + (t * local_ray.direction.x);
	z = local_ray.origin.z + (t * local_ray.direction.z);
	r_squared = (x * x) + (z * z);
	if (r_squared > 1.0)
		return (FALSE);
	record->t = t;
	set_disk_record(object, world_ray, &local_ray, record);
	return (TRUE);
}
