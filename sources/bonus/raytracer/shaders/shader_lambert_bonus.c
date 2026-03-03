/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_lambert_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 20:03:10 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 17:01:15 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_color	shader_lambert(t_scene *scene, t_hit_record *record, t_color albedo)
{
	t_color	total_light;
	t_color	diffuse;
	t_light	*light;
	t_color	shadow;

	total_light = color_scale(color_prod(scene->ambient, albedo),
			compute_ao(scene, record));
	light = scene->lights;
	while (light)
	{
		shadow = get_shadow_factor(scene, record, light);
		if (light->active && color_mean(shadow) > 0.01)
		{
			diffuse = compute_diffuse(light, record, albedo);
			total_light = color_add(total_light, color_prod(diffuse,
						shadow));
		}
		light = light->next;
	}
	return (total_light);
}
