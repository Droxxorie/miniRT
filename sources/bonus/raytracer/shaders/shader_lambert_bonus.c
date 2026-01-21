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
	t_real	shadow_factor;
	t_real	ao_factor;

	ao_factor = compute_ao(scene, record);
	total_light = color_scale(color_prod(scene->ambient, albedo), ao_factor);
	light = scene->lights;
	while (light)
	{
		shadow_factor = get_shadow_factor(scene, record, light);
		if (light->active && shadow_factor > 0.01)
		{
			diffuse = compute_diffuse(light, record, albedo);
			total_light = color_add(total_light, color_scale(diffuse,
						shadow_factor));
		}
		light = light->next;
	}
	return (total_light);
}
