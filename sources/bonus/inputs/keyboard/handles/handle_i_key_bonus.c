/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_i_key_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:23:34 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 12:32:52 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	handle_i_key(t_scene *scene)
{
	if (scene->selected_object)
		log_object_info(scene->selected_object);
	else if (scene->selected_light)
		log_light_info(scene->selected_light);
	else
		log_camera_info(scene->active_camera);
}
