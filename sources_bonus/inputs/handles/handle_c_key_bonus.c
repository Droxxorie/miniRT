/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_c_key_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:58:23 by eraad             #+#    #+#             */
/*   Updated: 2026/01/07 12:43:20 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	handle_c_key(t_scene *scene)
{
	if (scene->selected_object != NULL || scene->selected_light != NULL)
	{
		scene->selected_object = NULL;
		scene->selected_light = NULL;
		log_event("INFO", "Switched to camera ID: ",
			scene->active_camera->id);
	}
}
