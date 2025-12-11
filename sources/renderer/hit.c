/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:47:45 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 22:55:04 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_bool	hit(t_object *objects, t_ray *ray, t_hit_record *record)
{
	t_bool	is_hit;

	is_hit = FALSE;
	if (objects->type == SPHERE)
		is_hit = hit_sphere(&objects->data.sphere, ray, record);
	else if (objects->type == PLANE)
		is_hit = hit_plane(&objects->data.plane, ray, record); // TODO
	else if (objects->type == CYLINDER)
		is_hit = hit_cylinder(&objects->data.cylinder, ray, record); // TODO
	if (is_hit)
		record->object = objects;
	return (is_hit);
}

t_bool	hit_objects(t_object *objects, t_ray *ray, t_hit_record *record)
{
	t_bool			hit_anything;
	t_hit_record	temp_record;

	hit_anything = FALSE;
	while (objects)
	{
		if (hit(objects, ray, &temp_record)) // TODO
		{
			hit_anything = TRUE;
			ray->max = temp_record.t;
			*record = temp_record;
		}
		objects = objects->next;
	}
	return (hit_anything);
}