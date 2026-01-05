/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_click_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:03:42 by eraad             #+#    #+#             */
/*   Updated: 2026/01/04 13:08:45 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	handle_left_click(t_scene *scene, int x, int y)
{
	t_ray			ray;
	t_hit_record	record;

	scene->selected_object = NULL;
	scene->selected_light = NULL;
	generate_ray(scene->active_camera, &ray, (t_real)x, (t_real)y);
	if (hit_objects(scene->objects, &ray, &record)
		&& record.object != scene->selected_object)
	{
		scene->selected_object = record.object;
		ft_putstr_fd("Switched to object control mode\n", 1);
		print_object_details(record.object->type);
	}
}
