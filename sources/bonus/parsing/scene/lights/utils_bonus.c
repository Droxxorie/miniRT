/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:42:49 by eraad             #+#    #+#             */
/*   Updated: 2026/01/22 12:08:25 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	init_quad_light(t_light *light)
{
	t_vec3	up;

	if (fabs(light->direction.y) < 0.999)
		up = (t_vec3){0.0, 1.0, 0.0};
	else
		up = (t_vec3){0.0, 0.0, 1.0};
	light->u = vec3_normalize(vec3_cross(up, light->direction));
	light->v = vec3_normalize(vec3_cross(light->direction, light->u));
	light->u = vec3_scale(light->u, light->width);
	light->v = vec3_scale(light->v, light->height);
}

void	init_spot_light(t_light *light, t_real cutoff_angle)
{
	t_real	theta;

	cutoff_angle = ft_clamp(cutoff_angle, 0.0, 180.0);
	theta = cutoff_angle * PI / 180.0;
	light->cos_theta = cos(theta);
}

t_light	*alloc_new_light(t_scene *scene, char **line)
{
	t_light	*new_light;
	int		count;

	count = get_light_count(scene->lights);
	if (count >= MAX_LIGHTS)
	{
		print_error_limit(scene, *line - 1, "lights", MAX_LIGHTS);
		return (NULL);
	}
	new_light = ft_calloc(1, sizeof(t_light));
	if (new_light == NULL)
	{
		sys_print_error(ERR_MEM_LIGHT);
		return (NULL);
	}
	new_light->id = count + 1;
	new_light->active = TRUE;
	return (new_light);
}

void	add_light_to_scene(t_scene *scene, t_light *new_light)
{
	t_light	*current;

	if (scene->lights == NULL)
		scene->lights = new_light;
	else
	{
		current = scene->lights;
		while (current->next)
			current = current->next;
		current->next = new_light;
	}
}
