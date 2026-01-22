/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:40:02 by eraad             #+#    #+#             */
/*   Updated: 2026/01/22 15:59:42 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_color	compute_diffuse(t_light *light, t_hit_record *record, t_color albedo)
{
	t_vec3	light_dir;
	t_real	dist;
	t_real	diffuse;
	t_real	spot;
	t_real	attenuation;

	get_light_data(light, record->hit_point, &light_dir, &dist);
	spot = get_spot_factor(light, light_dir);
	if (spot <= 0.0)
		return ((t_color){0.0, 0.0, 0.0});
	diffuse = fmax(vec3_dot(record->normal, light_dir), 0.0);
	attenuation = get_light_attenuation(light, dist);
	diffuse = diffuse * attenuation * spot * light->brightness;
	return (color_scale(color_prod(light->color, albedo), diffuse));
}
