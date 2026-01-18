/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_model_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:10:04 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 18:53:48 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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

	shininess = 32.0; // TODO make it configurable per material
	dir = vec3_normalize(vec3_sub(light->position, record->hit_point));
	view_dir = vec3_normalize(vec3_scale(ray->direction, -1.0));
	reflect_dir = vec_reflect(vec3_scale(dir, -1.0), record->normal);
	specular = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), shininess);
	return (color_scale(light->color, light->brightness * specular));
}

static t_color	compute_light_contribution(t_scene *scene, t_light *light,
		t_hit_record *record, t_ray *ray)
{
	t_color	diffuse;
	t_color	specular;
	t_color	contribution;
	t_real	shadow_factor;

	if (light->active == FALSE)
		return ((t_color){0.0, 0.0, 0.0});
	shadow_factor = get_shadow_factor(scene, record, light);
	if (shadow_factor <= 0.01)
		return ((t_color){0.0, 0.0, 0.0});
	diffuse = color_prod(compute_diffuse(light, record), record->color);
	specular = compute_specular(light, record, ray);
	contribution = color_add(diffuse, specular);
	return (color_scale(contribution, shadow_factor));
}

t_color	phong_light(t_scene *scene, t_hit_record *record, t_ray *ray)
{
	t_color	total_light;
	t_color	ambient_part;
	t_light	*current_light;
	t_color	light_contribution;
	t_real	ao_factor;

	ambient_part = color_prod(scene->ambient, record->color);
	ao_factor = compute_ao(scene, record);
	total_light = color_scale(ambient_part, ao_factor);
	current_light = scene->lights;
	while (current_light)
	{
		light_contribution = compute_light_contribution(scene, current_light,
				record, ray);
		total_light = color_add(total_light, light_contribution);
		current_light = current_light->next;
	}
	return (total_light);
}
