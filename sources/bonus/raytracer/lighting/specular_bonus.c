/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:40:21 by eraad             #+#    #+#             */
/*   Updated: 2026/01/22 15:59:49 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

//* dirs[0] = light_dir
//* dirs[1] = view_dir
//* dirs[2] = half_dir
t_color	compute_specular(t_light *light, t_hit_record *record, t_ray *ray,
		t_real shininess)
{
	t_vec3	dirs[3];
	t_real	dist;
	t_real	angle;
	t_color	specular;
	t_real	attenuation;

	get_light_data(light, record->hit_point, &dirs[0], &dist);
	if (get_spot_factor(light, dirs[0]) <= 0.0)
		return ((t_color){0.0, 0.0, 0.0});
	dirs[1] = vec3_normalize(vec3_scale(ray->direction, -1.0));
	dirs[2] = vec3_normalize(vec3_add(dirs[0], dirs[1]));
	angle = fmaxf(vec3_dot(record->normal, dirs[2]), 0.0);
	if (record->object->material && record->object->material->specular_map)
		specular = sample_texture(record->object->material->specular_map,
				record->u, record->v);
	else if (record->object->material)
		specular = record->object->material->specular_color;
	else
		specular = (t_color){1.0, 1.0, 1.0};
	attenuation = get_light_attenuation(light, dist);
	attenuation = attenuation * light->brightness * powf(angle, shininess);
	return (color_scale(color_prod(light->color, specular), attenuation));
}
