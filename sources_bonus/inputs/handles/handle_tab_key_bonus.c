/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tab_key_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:08:54 by eraad             #+#    #+#             */
/*   Updated: 2026/01/11 23:57:19 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	handle_tab_key(t_scene *scene)
{
	if (scene->control_mode == TRANSLATE)
	{
		scene->control_mode = ROTATE;
		if (scene->selected_object
			&& scene->selected_object->type == TORUS)
			log_event(stdout, "WARN",
				"Torus rotation not supported (Complex primitive)");
		else if (scene->selected_light)
			log_event(stdout, "WARNING", "Lights cannot be rotated");
		else
			log_event(stdout, "INFO", "Switched to ROTATE mode");
	}
	else
	{
		scene->control_mode = TRANSLATE;
		log_event(stdout, "INFO", "Switched to TRANSLATE mode");
	}
}
