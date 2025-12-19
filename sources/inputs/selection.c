/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:25:30 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 19:25:48 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_bool	try_select_light(t_scene *scene, t_ray *ray)
{
	t_light	*current_light;

	current_light = scene->lights;
	while (current_light)
	{
		if (hit_light(current_light, ray, 2.0) == TRUE)
		{
			scene->selected_light = current_light;
			ft_putstr_fd("Switched to light control mode\n", 1);
			return (TRUE);
		}
		current_light = current_light->next;
	}
	return (FALSE);
}

t_bool	hit_light(t_light *light, t_ray *ray, t_real hit_radius)
{
	t_vec3 oc;
	t_real a;
	t_real b;
	t_real c;

	oc = vec3_sub(ray->origin, light->position);
	a = vec3_len_squared(ray->direction);
	b = 2.0 * vec3_dot(oc, ray->direction);
	c = vec3_len_squared(oc) - (hit_radius * hit_radius);
	return (b * b - 4 * a * c > 0);
}
