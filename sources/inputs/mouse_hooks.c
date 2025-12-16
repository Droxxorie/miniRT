/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:13:58 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 11:14:00 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_bool	try_select_light(t_scene *scene, t_ray *ray)
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

static void	handle_left_click(t_scene *scene, int x, int y)
{
	t_ray			ray;
	t_hit_record	record;
	t_real			u;
	t_real			v;

	scene->selected_object = NULL;
	scene->selected_light = NULL;
	u = (t_real)x / (t_real)(scene->mlx_window.width - 1);
	v = (t_real)(scene->mlx_window.height - 1 - y)
		/ (t_real)(scene->mlx_window.height - 1);
	get_ray(scene->active_camera, &ray, u, v);
	if (try_select_light(scene, &ray))
		return ;
	if (hit_objects(scene->objects, &ray, &record))
	{
		scene->selected_object = record.object;
		ft_putstr_fd("Switched to object control mode: ", 1);
		print_object_type(record.object->type);
	}
}

static void	hanlde_right_click(t_scene *scene)
{
	scene->selected_object = NULL;
	scene->selected_light = NULL;
	ft_putstr_fd("Switched to camera control mode\n", 1);
}

int	mouse_hook(int button, int x, int y, t_scene *scene)
{
	t_ray			ray;
	t_hit_record	record;
	t_light			*current_light;
	t_real			u;
	t_real			v;

	if (button == RIGHT_CLICK)
		hanlde_right_click(scene);
	else if (button == LEFT_CLICK)
		handle_left_click(scene, x, y);
	return (EXIT_SUCCESS);
}
