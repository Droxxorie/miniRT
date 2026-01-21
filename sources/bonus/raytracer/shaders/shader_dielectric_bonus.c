/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_dielectric_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:35:36 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 17:57:02 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_real	get_ior_ratio(t_hit_record *record)
{
	if (record->front_face)
		return (1.0 / record->object->material->ior);
	else
		return (record->object->material->ior);
}

static t_vec3	get_dielectric_dir(t_vec3 dir, t_vec3 normal, t_real ratio)
{
	t_real	cos_theta;
	t_real	sin_theta;
	t_vec3	unit_dir;

	unit_dir = vec3_normalize(dir);
	cos_theta = fmin(vec3_dot(vec3_scale(unit_dir, -1), normal), 1.0);
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	if (ratio * sin_theta > 1.0 || reflectance(cos_theta,
			ratio) > random_real())
		return (vec_reflect(unit_dir, normal));
	return (vec_refract(unit_dir, normal, ratio));
}

t_color	shader_dielectric(t_scene *scene, t_hit_record *rec, t_ray *ray,
		int depth)
{
	t_color	attenuation;
	t_real	n_ratio;
	t_vec3	direction;
	t_ray	scattered;
	t_vec3	offset;

	attenuation = get_albedo(rec->object->material, rec);
	n_ratio = get_ior_ratio(rec);
	direction = get_dielectric_dir(ray->direction, rec->normal, n_ratio);
	offset = vec3_scale(direction, EPSILON);
	scattered = new_ray(vec3_add(rec->hit_point, offset), direction);
	return (color_prod(attenuation, cast_ray(scene, &scattered, depth - 1)));
}
