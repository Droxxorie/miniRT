/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:14:11 by eraad             #+#    #+#             */
/*   Updated: 2025/12/15 14:18:22 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	dispatch_resize(t_object *object, int key)
{
	int i;
	static t_resize_map resize_map[] = {
		{SPHERE, resize_sphere},
		{CYLINDER, resize_cylinder},
		{NONE, NULL}
	};

	if (!object)
		return ;
	i = 0;
	while (resize_map[i].type != NONE)
	{
		if (resize_map[i].type == object->type)
		{
			resize_map[i].func(object, key);
			return ;
		}
		i++;
	}
}

void	dispatch_translate(t_object *object, t_vec3 translation)
{
	int i;
	static t_translate_map translate_map[] = {
		{SPHERE, translate_sphere},
		{CYLINDER, translate_cylinder},
		{PLANE, translate_plane},
		{NONE, NULL}
	};

	if (!object)
		return ;
	i = 0;
	while (translate_map[i].type != NONE)
	{
		if (translate_map[i].type == object->type)
		{
			translate_map[i].func(object, translation);
			return ;
		}
		i++;
	}
}

void	dispatch_rotate(t_object *object, t_vec3 rot_axis)
{
	int i;
	static t_translate_map rotate_map[] = {
		{CYLINDER, rotate_cylinder},
		{PLANE, rotate_plane},
		{NONE, NULL}
	};

	if (!object)
		return ;
	i = 0;
	while (rotate_map[i].type != NONE)
	{
		if (rotate_map[i].type == object->type)
		{
			rotate_map[i].func(object, rot_axis);
			return ;
		}
		i++;
	}
}
