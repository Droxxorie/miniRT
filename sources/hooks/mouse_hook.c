/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:22:36 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 22:42:08 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	mouse_hook(int button, int x, int y, t_scene *scene)
{
	t_ray			ray;
	t_hit_record	record;
	t_real			u;
	t_real			v;

	if (button == RIGHT_CLICK)
	{
		scene->selected_object = NULL;
		ft_putstr_fd("Switched to camera control mode\n", 1);
		return (0);
	}
	else if (button == LEFT_CLICK)
	{
		u = (t_real)x / (t_real)(scene->mlx_window.width - 1);
		v = (t_real)(scene->mlx_window.height - 1 - y) / (t_real)(scene->mlx_window.height - 1);
		get_ray(scene->active_camera, &ray, u, v);
		if (hit_objects(scene->objects, &ray, &record))
		{
			scene->selected_object = record.object;
			ft_putstr_fd("Switched to object control mode: ", 1);
			print_object_type(record.object->type);
		}
		return (0);
	}
	return (1); //? ou return 0 ?
}
