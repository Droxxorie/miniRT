/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_l_key_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:27:31 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 12:50:44 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	handle_l_key(t_scene *scene)
{
	if (scene->selected_light == NULL)
	{
		scene->selected_light = scene->lights;
		scene->selected_object = NULL;
		log_event(stdout, "INFO", "Switched to light ID: %d\n",
			scene->selected_light->id);
	}
}
