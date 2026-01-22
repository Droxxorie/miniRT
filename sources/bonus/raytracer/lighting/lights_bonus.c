/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:31:34 by eraad             #+#    #+#             */
/*   Updated: 2026/01/22 14:55:18 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	get_light_data(t_light *light, t_vec3 hit_point, t_vec3 *light_dir,
		t_real *distance)
{
	if (light->type == LIGHT_SUN)
	{
		*light_dir = vec3_normalize(vec3_scale(light->direction, -1.0));
		*distance = INFINITY;
	}
	else
	{
		*light_dir = vec3_sub(light->position, hit_point);
		*distance = vec3_len(*light_dir);
		*light_dir = vec3_normalize(*light_dir);
	}
}

t_real	get_spot_factor(t_light *light, t_vec3 light_dir)
{
	t_real	theta;
	t_vec3	spot_dir;
	t_real	epsilon;
	t_real	intensity;

	if (light->type != LIGHT_SPOT)
		return (1.0);
	spot_dir = vec3_normalize(light->direction);
	theta = vec3_dot(vec3_scale(light_dir, -1.0), spot_dir);
	epsilon = 0.01;
	intensity = ft_clamp((theta - light->cos_theta) / epsilon, 0.0, 1.0);
	return (intensity);
}

t_real	get_light_attenuation(t_light *light, t_real dist)
{
	t_real	attenuation;

	if (light->type == LIGHT_SUN)
		return (1.0);
	attenuation = 1.0 / (dist * dist * 0.5 + 1.0);
	return (attenuation);
}
