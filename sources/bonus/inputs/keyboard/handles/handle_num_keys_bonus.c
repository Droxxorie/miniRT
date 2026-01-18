/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_num_keys_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:46:03 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 19:46:29 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	handle_num_keys(t_scene *scene, int key)
{
	if (key == KEY_1)
	{
		scene->render_mode = RENDER_IMAGE;
		log_event(stdout, "WARN", "Render mode set to: IMAGE\n");
	}
	else if (key == KEY_2)
	{
		log_event(stdout, "WARN", "Render mode set to: NORMAL\n");
		scene->render_mode = RENDER_NORMAL;
	}
	else if (key == KEY_3)
	{
		log_event(stdout, "WARN", "Render mode set to: AO\n");
		scene->render_mode = RENDER_AO;
	}
}
