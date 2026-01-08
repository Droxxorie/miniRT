/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:09:52 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 22:25:21 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_bool	hit_dispatch(t_object *object, t_ray *ray,
	t_hit_record *record)
{
	int					i;
	static t_hit_map	map[] = {
	{SPHERE, hit_sphere},
	{PLANE, hit_plane},
	{CYLINDER, hit_cylinder},
	{RECTANGLE, hit_rectangle},
	{DISK, hit_disk},
	{TRIANGLE, hit_triangle},
	{NONE, NULL}};

	i = 0;
	while (map[i].type != NONE)
	{
		if (object->type == map[i].type)
			return (map[i].func(object, ray, record));
		i++;
	}
	return (FALSE);
}

t_bool	hit_objects(t_object *objects, t_ray *ray, t_hit_record *record)
{
	t_bool			hit_anything;
	t_hit_record	temp_record;

	hit_anything = FALSE;
	temp_record.need_details = TRUE;
	while (objects)
	{
		if (objects->visible == FALSE)
		{
			objects = objects->next;
			continue ;
		}
		if (hit_dispatch(objects, ray, &temp_record))
		{
			hit_anything = TRUE;
			ray->max = temp_record.t;
			*record = temp_record;
		}
		objects = objects->next;
	}
	return (hit_anything);
}

t_bool	hit_anything(t_object *objects, t_ray *ray)
{
	t_hit_record	temp_record;

	temp_record.need_details = FALSE;
	temp_record.t = ray->max;
	while (objects)
	{
		if (objects->visible == FALSE)
		{
			objects = objects->next;
			continue ;
		}
		if (hit_dispatch(objects, ray, &temp_record))
			return (TRUE);
		objects = objects->next;
	}
	return (FALSE);
}
