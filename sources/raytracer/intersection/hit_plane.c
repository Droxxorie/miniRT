/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:50:13 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 08:00:42 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_bool	hit_plane(t_object *object, t_ray *ray, t_hit_record *record)
{
	t_plane	*plane;
	t_real	denominator;
	t_real	root;

	plane = &object->u_data.plane;
	denominator = vec3_dot(ray->direction, plane->normal);
	if (fabs(denominator) < EPSILON)
		return (FALSE);
	root = -(vec3_dot(ray->origin, plane->normal) + plane->d) / denominator;
	if (root < ray->min || root > ray->max)
		return (FALSE);
	record->t = root;
	record->hit_point = vec3_add(ray->origin, vec3_scale(ray->direction, root));
	set_face_normal(record, ray, plane->normal);
	record->color = object->color;
	return (TRUE);
}
