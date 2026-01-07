/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tab_key_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:08:54 by eraad             #+#    #+#             */
/*   Updated: 2026/01/07 01:00:02 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	handle_tab_key(t_scene *scene)
{
	if (scene->control_mode == TRANSLATE)
	{
		scene->control_mode = ROTATE;
		if (scene->selected_object && scene->selected_object->type == SPHERE)
			ft_putstr_fd("Warning: Spheres cannot be rotated.\n",
				STDOUT_FILENO);
		else if (scene->selected_light)
			ft_putstr_fd("Warning: Lights cannot be rotated.\n", STDOUT_FILENO);
		else
			// print_render_log("Mode: ROTATE");
			ft_putstr_fd("\r\033[2KMode: ROTATE", STDOUT_FILENO);
	}
	else
	{
		scene->control_mode = TRANSLATE;
		ft_putstr_fd("\033[2KMode: TRANSLATE", STDOUT_FILENO);
		// print_render_log("Mode: TRANSLATE");
	}
}
