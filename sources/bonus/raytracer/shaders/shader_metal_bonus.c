/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_metal_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:30:28 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 18:59:06 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_vec3	generate_fuzz(t_hit_record *record)
{
	unsigned int	seed;
	t_vec3			fuzz;

	seed = generate_seed(record->hit_point);
	fuzz = vec3_scale(random_in_unit_sphere(&seed),
			record->object->material->roughness);
	return (fuzz);
}

t_color	shader_metal(t_scene *scene, t_hit_record *record, t_ray *ray,
		int depth)
{
	t_vec3	reflected;
	t_vec3	fuzz;
	t_ray	scattered;
	t_color	attenuation;
	t_color	bounce_color;

	reflected = vec_reflect(vec3_normalize(ray->direction), record->normal);
	if (record->object->material->roughness > 0.0)
	{
		fuzz = generate_fuzz(record);
		reflected = vec3_add(reflected, fuzz);
	}
	scattered = new_ray(vec3_add(record->hit_point, vec3_scale(record->normal,
					EPSILON)), reflected);
	if (vec3_dot(scattered.direction, record->normal) <= 0)
		return ((t_color){0.0, 0.0, 0.0});
	attenuation = get_albedo(record->object->material, record);
	bounce_color = cast_ray(scene, &scattered, depth - 1);
	return (color_prod(attenuation, bounce_color));
}
