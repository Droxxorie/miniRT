/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_t_key_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 22:55:18 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 16:09:37 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	handle_t_key(t_scene *scene)
{
	if (scene->selected_object)
	{
		scene->selected_object->visible = !scene->selected_object->visible;
		log_event(stdout, "WARN", "Toggled visibility (%s)\n",
			get_object_type_str(scene->selected_object->type));
	}
	else if (scene->selected_light)
	{
		scene->selected_light->active = !scene->selected_light->active;
		log_event(stdout, "WARN", "Toggled light ID: %d\n",
			scene->selected_light->id);
	}
}
