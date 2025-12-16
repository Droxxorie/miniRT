/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:16:27 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 20:48:49 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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

void	action_selection(t_scene *scene, t_vec3 input_vector)
{
	if (scene->selected_object)
	{
		if (scene->control_mode == TRANSLATE)
			dispatch_translate(scene->selected_object, vec3_scale(input_vector,
					STEP_MOVE));
		else if (scene->control_mode == ROTATE)
			dispatch_rotate(scene->selected_object, vec3_scale(input_vector,
					STEP_ROT));
	}
	else if (scene->selected_light)
	{
		if (scene->control_mode == TRANSLATE)
			translate_light(scene->selected_light, vec3_scale(input_vector,
					STEP_MOVE));
		else
			ft_putstr_fd("Light rotation not supported\n", STDOUT_FILENO);
	}
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

void	switch_camera_next(t_scene *scene)
{
	static int	camera_index;

	if (!scene || !scene->cameras)
		return ;
	camera_index = 1;
	if (scene->active_camera->next)
	{
		scene->active_camera = scene->active_camera->next;
		camera_index++;
	}
	else
	{
		scene->active_camera = scene->cameras;
		camera_index = 1;
	}
	ft_putstr_fd("Switched to camera ID: ", 1);
	ft_putnbr_fd(camera_index, 1);
	ft_putstr_fd("\n", 1);
}

t_vec3	get_input_vector(int key)
{
	t_vec3	input_vector;

	input_vector = (t_vec3){0.0, 0.0, 0.0};
	if (key == KEY_UP || key == KEY_Z)
		input_vector.y = 1;
	if (key == KEY_DOWN || key == KEY_S)
		input_vector.y = -1;
	if (key == KEY_LEFT || key == KEY_Q)
		input_vector.x = -1;
	if (key == KEY_RIGHT || key == KEY_D)
		input_vector.x = 1;
	if (key == KEY_A)
		input_vector.z = 1;
	if (key == KEY_E)
		input_vector.z = -1;
	return (input_vector);
}
