/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_dielectric_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:35:36 by eraad             #+#    #+#             */
/*   Updated: 2026/01/24 11:44:54 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_color	beer_lambert(t_color color, t_real dist,
		t_color absorbance)
{
	t_color	transmission;

	transmission.r = exp(-absorbance.r * dist);
	transmission.g = exp(-absorbance.g * dist);
	transmission.b = exp(-absorbance.b * dist);
	return (color_prod(color, transmission));
}

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

t_color	shader_dielectric(t_scene *s, t_hit_record *rec, t_ray *ray, int depth)
{
	t_real	n_ratio;
	t_vec3	direction;
	t_ray	scattered;
	t_color	final_color;

	n_ratio = get_ior_ratio(rec);
	direction = get_dielectric_dir(ray->direction, rec->normal, n_ratio);
	scattered = new_ray(vec3_add(rec->hit_point, vec3_scale(direction,
					EPSILON)), direction);
	final_color = cast_ray(s, &scattered, depth - 1);
	if (rec->front_face == FALSE)
		final_color = beer_lambert(final_color, rec->t,
				rec->object->material->absorbance);
	return (final_color);
}
