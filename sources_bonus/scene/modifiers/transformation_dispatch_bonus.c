/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_dispatch_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:19:11 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 20:54:51 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	dispatch_resize(t_object *object, int mode, int direction)
{
	int					i;
	static t_resize_map	map[] = {
	{SPHERE, resize_sphere},
	{CYLINDER, resize_cylinder},
	{RECTANGLE, resize_rectangle},
	{DISK, resize_disk},
	{TRIANGLE, resize_triangle},
	{TORUS, resize_torus},
	{CONE, resize_cone},
	{NONE, NULL}};

	if (!object)
		return ;
	i = 0;
	while (map[i].type != NONE)
	{
		if (map[i].type == object->type)
		{
			map[i].func(object, mode, direction);
			return ;
		}
		i++;
	}
}

void	dispatch_translate(t_object *object, t_vec3 translation)
{
	int						i;
	static t_translate_map	map[] = {
	{SPHERE, translate_sphere},
	{CYLINDER, translate_cylinder},
	{PLANE, translate_plane},
	{RECTANGLE, translate_rectangle},
	{DISK, translate_disk},
	{TRIANGLE, translate_triangle},
	{TORUS, translate_torus},
	{CONE, translate_cone},
	{NONE, NULL}};

	if (!object)
		return ;
	i = 0;
	while (map[i].type != NONE)
	{
		if (map[i].type == object->type)
		{
			map[i].func(object, translation);
			return ;
		}
		i++;
	}
}

void	dispatch_rotate(t_object *object, t_vec3 rot_axis)
{
	int						i;
	static t_translate_map	map[] = {
	{CYLINDER, rotate_cylinder},
	{PLANE, rotate_plane},
	{RECTANGLE, rotate_rectangle},
	{DISK, rotate_disk},
	{TRIANGLE, rotate_triangle},
	{CONE, rotate_cone},
	{NONE, NULL}};

	if (!object)
		return ;
	i = 0;
	while (map[i].type != NONE)
	{
		if (map[i].type == object->type)
		{
			map[i].func(object, rot_axis);
			return ;
		}
		i++;
	}
}
