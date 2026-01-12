/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:13:58 by eraad             #+#    #+#             */
/*   Updated: 2026/01/04 13:37:10 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

int	mouse_hook(int button, int x, int y, t_scene *scene)
{
	t_bool	render_needed;

	render_needed = FALSE;
	if (button == LEFT_CLICK)
		handle_left_click(scene, x, y);
	else if (button == SCROLL_UP || button == SCROLL_DOWN)
		if (handle_scroll(button, scene) == TRUE)
			render_needed = TRUE;
	if (render_needed == TRUE)
		render_frame(scene);
	return (EXIT_SUCCESS);
}
