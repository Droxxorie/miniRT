/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_rectangle_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:53:23 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 21:17:24 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	set_rectangle_record(t_object *object, t_ray *world_ray,
		t_ray *local_ray, t_hit_record *record)
{
	t_vec3		local_normal;
	t_point3	local_hit_point;

	record->hit_point = ray_at(world_ray, record->t);
	record->color = object->color;
	record->object = object;
	if (world_ray->is_shadow_ray == TRUE)
		return ;
	if (local_ray->direction.y > 0)
		local_normal = (t_vec3){0, -1, 0};
	else
		local_normal = (t_vec3){0, 1, 0};
	local_hit_point = ray_at(local_ray, record->t);
	get_rectangle_uv(local_hit_point, &record->u, &record->v);
	record->normal = mat4_mult_vec3(object->transposed_inverse, local_normal);
	record->normal = vec3_normalize(record->normal);
	set_face_normal(record, world_ray, record->normal);
}

t_bool	hit_rectangle(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_ray	local_ray;
	t_real	t;
	t_real	x;
	t_real	z;

	local_ray = transform_ray(*world_ray, object->inverse);
	if (fabs(local_ray.direction.y) < EPSILON)
		return (FALSE);
	t = -local_ray.origin.y / local_ray.direction.y;
	if (t < world_ray->min || t > world_ray->max)
		return (FALSE);
	x = local_ray.origin.x + (t * local_ray.direction.x);
	z = local_ray.origin.z + (t * local_ray.direction.z);
	if (fabs(x) > 0.5 || fabs(z) > 0.5)
		return (FALSE);
	record->t = t;
	set_rectangle_record(object, world_ray, &local_ray, record);
	return (TRUE);
}
