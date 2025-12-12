/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:47:45 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 19:17:06 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_bool	hit(t_object *object, t_ray *ray, t_hit_record *record)
{
	int i;
	static t_hit_dispatch hit_dispatch[] = {
		{SPHERE, hit_sphere},
		{PLANE, hit_plane},
		{CYLINDER, hit_cylinder},
		{NONE, NULL}
	};

	i = 0;
	while (hit_dispatch[i].type != NONE)
	{
		if (object->type == hit_dispatch[i].type)
			return (hit_dispatch[i].func(object, ray, record));
		i++;
	}
	return (FALSE);
}

t_bool	hit_objects(t_object *objects, t_ray *ray, t_hit_record *record)
{
	t_bool			hit_anything;
	t_hit_record	temp_record;

	hit_anything = FALSE;
	while (objects)
	{
		if (hit(objects, ray, &temp_record))
		{
			hit_anything = TRUE;
			ray->max = temp_record.t;
			*record = temp_record;
		}
		objects = objects->next;
	}
	return (hit_anything);
}
