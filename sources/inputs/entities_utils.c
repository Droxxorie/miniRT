/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 21:01:09 by eraad             #+#    #+#             */
/*   Updated: 2025/12/18 21:02:33 by eraad            ###   ########.fr       */
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
	t_vec3	oc;
	t_real	a;
	t_real	b;
	t_real	c;

	oc = vec3_sub(ray->origin, light->position);
	a = vec3_len_squared(ray->direction);
	b = 2.0 * vec3_dot(oc, ray->direction);
	c = vec3_len_squared(oc) - (hit_radius * hit_radius);
	return (b * b - 4 * a * c > 0);
}

void	action_camera(t_scene *scene, t_vec3 input_vector)
{
	t_real	aspect_ratio;

	aspect_ratio = scene->mlx_window.aspect_ratio;
	if (scene->control_mode == TRANSLATE)
		translate_camera(scene->active_camera, vec3_scale(input_vector,
				STEP_MOVE), aspect_ratio);
	else if (scene->control_mode == ROTATE)
		rotate_camera(scene->active_camera, vec3_scale(input_vector, STEP_ROT),
			aspect_ratio);
}

void	switch_camera_next(t_scene *scene)
{
	if (!scene || !scene->cameras)
		return ;
	if (scene->active_camera->next)
		scene->active_camera = scene->active_camera->next;
	else
		scene->active_camera = scene->cameras;
	ft_putstr_fd("Switched to camera ID: ", 1);
	ft_putnbr_fd(scene->active_camera->id, 1);
	ft_putstr_fd("\n", 1);
}
