/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:09:52 by eraad             #+#    #+#             */
/*   Updated: 2026/01/11 21:35:30 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_bool	hit_dispatch(t_object *object, t_ray *ray, t_hit_record *record)
{
	int					i;
	static t_hit_map	map[] = {{SPHERE, hit_sphere}, {PLANE, hit_plane},
	{CYLINDER, hit_cylinder}, {RECTANGLE, hit_rectangle},
	{DISK, hit_disk}, {TRIANGLE, hit_triangle}, {TORUS, hit_torus},
	{CONE, hit_cone}, {BOX, hit_box}, {NONE, NULL}};

	i = 0;
	while (map[i].type != NONE)
	{
		if (object->type == map[i].type)
			return (map[i].func(object, ray, record));
		i++;
	}
	return (FALSE);
}

static t_bool	hit_objects_linear(t_object *objects, t_ray *ray,
		t_hit_record *record)
{
	t_bool			hit_anything;
	t_hit_record	temp_record;

	hit_anything = FALSE;
	temp_record.need_details = record->need_details;
	while (objects)
	{
		if (objects->visible)
		{
			if (hit_dispatch(objects, ray, &temp_record))
			{
				hit_anything = TRUE;
				ray->max = temp_record.t;
				*record = temp_record;
			}
		}
		objects = objects->next;
	}
	return (hit_anything);
}

t_bool	hit_objects(t_scene *scene, t_ray *ray, t_hit_record *record)
{
	record->need_details = TRUE;
	if (scene->bvh_root)
		return (hit_bvh(scene->bvh_root, ray, record));
	else
		return (hit_objects_linear(scene->objects, ray, record));
}

t_bool	hit_anything(t_scene *scene, t_ray *ray)
{
	t_hit_record	temp_record;

	temp_record.need_details = FALSE;
	if (scene->bvh_root)
		return (hit_bvh(scene->bvh_root, ray, &temp_record));
	else
		return (hit_objects_linear(scene->objects, ray, &temp_record));
}
