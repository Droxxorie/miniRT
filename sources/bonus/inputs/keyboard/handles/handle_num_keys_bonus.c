/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_num_keys_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:46:03 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 21:51:50 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	set_mode(t_scene *scene, t_render_mode mode, char *message)
{
	scene->render_mode = mode;
	log_event(stdout, "WARN", "Render mode set to: %s\n", message);
}

void	handle_num_keys(t_scene *scene, int key)
{
	if (key == KEY_1)
		set_mode(scene, RENDER_SHADE, "SHADE");
	else if (key == KEY_2)
		set_mode(scene, RENDER_NORMAL, "NORMAL");
	else if (key == KEY_3)
		set_mode(scene, RENDER_AO, "AO");
	else if (key == KEY_4)
		set_mode(scene, RENDER_DEPTH, "DEPTH");
	else if (key == KEY_5)
		set_mode(scene, RENDER_SHADOWS, "SHADOWS");
	else if (key == KEY_6)
		set_mode(scene, RENDER_OBJECT_ID, "OBJECT ID");
	else if (key == KEY_7)
		set_mode(scene, RENDER_UV, "UV");
}
