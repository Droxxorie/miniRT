/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_phong_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:46:00 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 17:01:04 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

//* dirs[0] = light_dir
//* dirs[1] = view_dir
//* dirs[2] = reflect_dir
static t_color	compute_specular(t_light *light, t_hit_record *record,
		t_ray *ray, t_real shininess)
{
	t_vec3		dirs[3];
	t_real		angle;
	t_color		specular;
	t_material	*mat;

	mat = record->object->material;
	dirs[0] = vec3_normalize(vec3_sub(light->position, record->hit_point));
	dirs[1] = vec3_normalize(vec3_scale(ray->direction, -1.0));
	dirs[2] = vec3_normalize(vec3_add(dirs[0], dirs[1]));
	angle = fmax(vec3_dot(record->normal, dirs[2]), 0.0);
	if (mat && mat->specular_map)
		specular = sample_texture(mat->specular_map, record->u, record->v);
	else if (mat)
		specular = mat->specular_color;
	else
		specular = (t_color){1.0, 1.0, 1.0};
	return (color_scale(color_prod(light->color, specular), light->brightness
			* pow(angle, shininess)));
}

t_color	compute_diffuse(t_light *light, t_hit_record *record, t_color albedo)
{
	t_vec3	light_dir;
	t_real	diffuse;

	light_dir = vec3_normalize(vec3_sub(light->position, record->hit_point));
	diffuse = fmax(vec3_dot(record->normal, light_dir), 0.0);
	return (color_scale(color_prod(light->color, albedo), light->brightness
			* diffuse));
}

//* parts[0] = diffuse
//* parts[1] = specular
//* factors[0] = shadow_factor
//* factors[1] = shininess
static t_color	accumulate_lights(t_scene *scene, t_hit_record *record,
		t_ray *ray, t_color albedo)
{
	t_light	*current;
	t_color	total_light;
	t_color	parts[2];
	t_real	factors[2];

	total_light = (t_color){0.0, 0.0, 0.0};
	current = scene->lights;
	factors[1] = get_shininess(record->object->material, record);
	if (factors[1] < 1.0)
		factors[1] = 32.0;
	while (current)
	{
		factors[0] = get_shadow_factor(scene, record, current);
		if (current->active && factors[0] > 0.01)
		{
			parts[0] = compute_diffuse(current, record, albedo);
			parts[1] = compute_specular(current, record, ray, factors[1]);
			total_light = color_add(total_light, color_scale(color_add(parts[0],
							parts[1]), factors[0]));
		}
		current = current->next;
	}
	return (total_light);
}

t_color	shader_phong(t_scene *scene, t_hit_record *record, t_ray *ray)
{
	t_color	ambient;
	t_color	albedo;
	t_real	ao_factor;
	t_color	accumulated_light;
	t_color	total_light;

	albedo = get_albedo(record->object->material, record);
	ao_factor = compute_ao(scene, record);
	ambient = color_scale(color_prod(scene->ambient, albedo), ao_factor);
	accumulated_light = accumulate_lights(scene, record, ray, albedo);
	total_light = color_add(ambient, accumulated_light);
	return (total_light);
}
