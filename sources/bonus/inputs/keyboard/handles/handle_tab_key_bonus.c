/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tab_key_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:08:54 by eraad             #+#    #+#             */
/*   Updated: 2026/01/22 23:37:17 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	handle_tab_key(t_scene *s)
{
	if (s->control_mode == TRANSLATE)
	{
		s->control_mode = ROTATE;
		if (s->selected_object && s->selected_object->type == TORUS)
			log_event(stdout, "WARN",
				"Torus rotation not supported (Complex primitive)\n");
		else if (s->selected_light && s->selected_light->type == LIGHT_POINT)
			log_event(stdout, "WARNING", "Lights point cannot be rotated\n");
		else
			log_event(stdout, "INFO", "Switched to ROTATE mode\n");
	}
	else
	{
		s->control_mode = TRANSLATE;
		log_event(stdout, "INFO", "Switched to TRANSLATE mode\n");
	}
}
