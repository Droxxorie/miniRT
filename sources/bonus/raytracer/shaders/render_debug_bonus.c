/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_debug_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:34:53 by eraad             #+#    #+#             */
/*   Updated: 2026/01/22 16:00:12 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_color	debug_lights_only(t_scene *scene, t_hit_record *record)
{
	t_color	white;

	white = (t_color){0.8, 0.8, 0.8};
	return (shader_lambert(scene, record, white));
}

static t_color	debug_checkerboard(t_hit_record *record)
{
	t_material	material;

	material.color = (t_color){1.0, 1.0, 1.0};
	material.uv_scale = 1.0;
	return (pattern_checker(record, &material));
}

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
	t_color	shadow_total;
	int		count;

	light = scene->lights;
	shadow_total = (t_color){0.0, 0.0, 0.0};
	count = 0;
	while (light)
	{
		if (light->active)
		{
			shadow_total = color_add(shadow_total, get_shadow_factor(scene,
						record, light));
			count++;
		}
		light = light->next;
	}
	if (count > 0)
		shadow_total = color_scale(shadow_total, 1.0 / (t_real)count);
	return (shadow_total);
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
	else if (scene->render_mode == RENDER_LIGHTS)
		return (debug_lights_only(scene, record));
	else if (scene->render_mode == RENDER_CHECKER)
		return (debug_checkerboard(record));
	return ((t_color){0.0, 0.0, 0.0});
}
