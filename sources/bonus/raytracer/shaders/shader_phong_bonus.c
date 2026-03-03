/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_phong_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:46:00 by eraad             #+#    #+#             */
/*   Updated: 2026/01/22 12:40:34 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

//* parts[0] = diffuse
//* parts[1] = specular
//* parts[2] = shadow
static t_color	accumulate_lights(t_scene *scene, t_hit_record *record,
		t_ray *ray, t_color albedo)
{
	t_light	*current;
	t_color	total_light;
	t_color	parts[3];
	t_real	shininess;

	total_light = (t_color){0.0, 0.0, 0.0};
	current = scene->lights;
	shininess = get_shininess(record->object->material, record);
	if (shininess < 1.0)
		shininess = 32.0;
	while (current)
	{
		parts[2] = get_shadow_factor(scene, record, current);
		if (current->active && color_mean(parts[2]) > 0.01)
		{
			parts[0] = compute_diffuse(current, record, albedo);
			parts[1] = compute_specular(current, record, ray, shininess);
			total_light = color_add(total_light, color_prod(color_add(
							parts[0], parts[1]), parts[2]));
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
