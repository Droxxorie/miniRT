/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:50:13 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 11:13:20 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	set_plane_record(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_vec3	local_normal;

	record->hit_point = vec3_add(world_ray->origin, vec3_scale(world_ray->direction,
				record->t));
	record->color = object->color;
	record->object = object;
	if (record->need_details == FALSE)
		return ;
	local_normal = (t_vec3){0.0, 1.0, 0.0};
	record->normal = vec3_normalize(mat4_mult_vec3(object->transposed_inverse, local_normal));
	set_face_normal(record, world_ray, record->normal);
}

t_bool	hit_plane(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_ray	object_ray;
	t_real t;
	
	object_ray = transform_ray(*world_ray, object->inverse);
	if (fabs(object_ray.direction.y) < EPSILON)
		return (FALSE);
	t = -object_ray.origin.y / object_ray.direction.y;
	if (t < world_ray->min || t > world_ray->max)
		return (FALSE);
	record->t = t;
	set_plane_record(object, world_ray, record);
	return (TRUE);
}
