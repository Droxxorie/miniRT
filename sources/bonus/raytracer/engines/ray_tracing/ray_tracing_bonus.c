/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:09:52 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 18:30:17 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_bool	ray_tracing(t_object *object, t_ray *ray, t_hit_record *record)
{
	if (object->type == SPHERE)
		return (hit_sphere(object, ray, record));
	else if (object->type == CYLINDER)
		return (hit_cylinder(object, ray, record));
	else if (object->type == RECTANGLE)
		return (hit_rectangle(object, ray, record));
	else if (object->type == DISK)
		return (hit_disk(object, ray, record));
	else if (object->type == TRIANGLE)
		return (hit_triangle(object, ray, record));
	else if (object->type == TORUS)
		return (hit_torus(object, ray, record));
	else if (object->type == CONE)
		return (hit_cone(object, ray, record));
	else if (object->type == BOX)
		return (hit_box(object, ray, record));
	else
		return (FALSE);
}
