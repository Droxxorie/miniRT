/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:31:34 by eraad             #+#    #+#             */
/*   Updated: 2026/01/27 17:02:37 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

//* uv_offset[0] = u_offset
//* uv_offset[1] = v_offset
t_vec3	get_light_sample(t_light *light, t_hit_record *record,
		unsigned int *seed)
{
	t_vec3	random_point;
	t_vec3	uv_offset[2];
	t_vec3	sun_source;
	t_vec3	jitter;
	t_real	r[2];

	if (light->type == LIGHT_SUN)
	{
		sun_source = vec3_scale(light->direction, -10000.0);
		jitter = vec3_scale(random_in_unit_sphere(seed), 50.0);
		return (vec3_add(record->hit_point, vec3_add(sun_source, jitter)));
	}
	else if (light->type == LIGHT_QUAD)
	{
		r[0] = random_double(seed) - 0.5;
		r[1] = random_double(seed) - 0.5;
		uv_offset[0] = vec3_scale(light->u, r[0]);
		uv_offset[1] = vec3_scale(light->v, r[1]);
		return (vec3_add(light->position, vec3_add(uv_offset[0],
					uv_offset[1])));
	}
	random_point = vec3_normalize(random_in_unit_sphere(seed));
	if (vec3_len_squared(random_point) < EPSILON)
		random_point = (t_vec3){1.0, 0.0, 0.0};
	return (vec3_add(light->position, vec3_scale(random_point, LIGHT_RADIUS)));
}

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
