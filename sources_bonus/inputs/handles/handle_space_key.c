/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:28:40 by eraad             #+#    #+#             */
/*   Updated: 2026/01/04 13:39:32 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	handle_space_key(t_scene *scene)
{
	if (scene->selected_light && scene->lights->id > 1)
		switch_light_next(scene);
	else if (!scene->selected_object && scene->active_camera->id > 1)
		switch_camera_next(scene);
}
