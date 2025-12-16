/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:10:04 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 11:10:11 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_bool	is_in_shadow(t_scene *scene, t_point3 hit_point,
		t_point3 light_pos)
{
	t_vec3			dir_to_light;
	t_real			dist_to_light;
	t_ray			shadow_ray;
	t_hit_record	record;

	dir_to_light = vec3_sub(light_pos, hit_point);
	dist_to_light = vec3_len(dir_to_light);
	dir_to_light = vec3_normalize(dir_to_light);
	shadow_ray.origin = vec3_add(hit_point, vec3_scale(dir_to_light, EPSILON));
	shadow_ray.direction = dir_to_light;
	shadow_ray.min = EPSILON;
	shadow_ray.max = dist_to_light;
	if (hit_objects(scene->objects, &shadow_ray, &record))
		return (TRUE);
	return (FALSE);
}

static t_color	compute_diffuse(t_light *light, t_hit_record *record)
{
	t_vec3	dir;
	t_real	diffuse_strength;
	t_color	diffuse;

	dir = vec3_sub(light->position, record->hit_point);
	dir = vec3_normalize(dir);
	diffuse_strength = fmax(vec3_dot(record->normal, dir), 0.0);
	diffuse = color_scale(light->color, light->brightness * diffuse_strength);
	return (diffuse);
}

static t_color	compute_specular(t_light *light, t_hit_record *record,
		t_ray *ray)
{
	t_vec3	dir;
	t_vec3	reflect_dir;
	t_vec3	view_dir;
	t_real	shininess;
	t_real	specular;

	shininess = 32.0; //* Temporaire pour tester
	dir = vec3_normalize(vec3_sub(light->position, record->hit_point));
	view_dir = vec3_normalize(vec3_scale(ray->direction, -1.0));
	reflect_dir = vec_reflect(vec3_scale(dir, -1.0), record->normal);
	specular = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), shininess);
	return (color_scale(light->color, light->brightness * specular));
}

t_color	phong_light(t_scene *scene, t_hit_record *record, t_ray *ray)
{
	t_color	total_light;
	t_color	light_contribution;
	t_light	*current_light;
	t_color	diffuse;
	t_color	specular;

	total_light = color_prod(scene->ambient, record->color);
	current_light = scene->lights;
	while (current_light)
	{
		light_contribution = (t_color){0.0, 0.0, 0.0};
		if (is_in_shadow(scene, record->hit_point,
				current_light->position) == FALSE)
		{
			diffuse = compute_diffuse(current_light, record);
			diffuse = color_prod(diffuse, record->color);
			light_contribution = color_add(light_contribution, diffuse);
			specular = compute_specular(current_light, record, ray);
			light_contribution = color_add(light_contribution, specular);
		}
		total_light = color_add(total_light, light_contribution);
		current_light = current_light->next;
	}
	return (total_light);
}
