/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_debug_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:34:53 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 21:57:17 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_color	debug_depth(t_hit_record *record)
{
	t_real	depth;
	t_real	sensitivity;

	sensitivity = 0.1;
	depth = 1.0 / (record->t * sensitivity + 1.0);
	return ((t_color){depth, depth, depth});
}

static t_color	debug_shadow(t_scene *scene, t_hit_record *record)
{
	t_light	*light;
	t_real	shadow_factor;
	int		count;

	light = scene->lights;
	shadow_factor = 0.0;
	count = 0;
	while (light)
	{
		if (light->active)
		{
			shadow_factor += get_shadow_factor(scene, record, light);
			count++;
		}
		light = light->next;
	}
	if (count > 0)
		shadow_factor /= (t_real)count;
	return ((t_color){shadow_factor, shadow_factor, shadow_factor});
}

static t_color	debug_object_id(t_object *object)
{
	unsigned long	id;
	t_color			color;

	id = (unsigned long)object;
	color.r = (t_real)((id & 0xFF0000) >> 16) / 255.0;
	color.g = (t_real)((id & 0x00FF00) >> 8) / 255.0;
	color.b = (t_real)(id & 0x0000FF) / 255.0;
	return (color);
}

t_color	render_debug(t_scene *scene, t_hit_record *record)
{
	t_real	ao_factor;

	if (scene->render_mode == RENDER_NORMAL)
		return ((t_color){(record->normal.x + 1.0) * 0.5, (record->normal.y
				+ 1.0) * 0.5, (record->normal.z + 1.0) * 0.5});
	else if (scene->render_mode == RENDER_AO)
	{
		ao_factor = compute_ao(scene, record);
		return ((t_color){ao_factor, ao_factor, ao_factor});
	}
	else if (scene->render_mode == RENDER_UV)
		return ((t_color){record->u, record->v, 0.0});
	else if (scene->render_mode == RENDER_DEPTH)
		return (debug_depth(record));
	else if (scene->render_mode == RENDER_SHADOWS)
		return (debug_shadow(scene, record));
	else if (scene->render_mode == RENDER_OBJECT_ID)
		return (debug_object_id(record->object));
	return ((t_color){0.0, 0.0, 0.0});
}
