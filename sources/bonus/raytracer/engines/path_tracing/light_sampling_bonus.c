/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_sampling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 16:29:10 by eraad             #+#    #+#             */
/*   Updated: 2026/01/27 16:47:09 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_color	sample_direct_lighting(t_scene *scene, t_hit_record *rec, t_vec3 v,
		t_path_info *info)
{
	t_color	direct_light;
	t_light	*light;

	direct_light = (t_color){0.0, 0.0, 0.0};
	light = scene->lights;
	while (light)
	{
		if (!light->active)
		{
			light = light->next;
			continue ;
		}
		if (scene->render_mode == RENDER_AO)
			direct_light = color_add(direct_light,
					debug_light_contribution(light, rec, info));
		else
			direct_light = color_add(direct_light,
					compute_light_contribution(light, rec, v, info));
		light = light->next;
	}
	return (direct_light);
}
