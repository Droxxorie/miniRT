/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:50:13 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 14:24:02 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	set_plane_record(t_object *object, t_ray *world_ray,
		t_hit_record *record)
{
	record->hit_point = vec3_add(world_ray->origin,
			vec3_scale(world_ray->direction, record->t));
	record->color = object->color;
	record->object = object;
	if (record->need_details == FALSE)
		return ;
	record->normal = object->u_data.plane.normal;
	set_face_normal(record, world_ray, record->normal);
}

//* t = ((P - O) * N) / (D * N)
t_bool	hit_plane(t_object *object, t_ray *world_ray, t_hit_record *record)
{
	t_plane	*plane;
	t_real	t;
	t_real	numerator;
	t_real	denominator;

	plane = &object->u_data.plane;
	denominator = vec3_dot(world_ray->direction, plane->normal);
	if (fabs(denominator) < EPSILON)
		return (FALSE);
	numerator = vec3_dot(vec3_sub(plane->origin, world_ray->origin),
			plane->normal);
	t = numerator / denominator;
	if (t < world_ray->min || t > world_ray->max)
		return (FALSE);
	record->t = t;
	set_plane_record(object, world_ray, record);
	return (TRUE);
}
