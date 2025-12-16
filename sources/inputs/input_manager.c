/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:55:33 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 11:47:34 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	input_manager(t_scene *scene)
{
	if (!scene || !scene->mlx_window.mlx_ptr || !scene->mlx_window.win_ptr)
		return ;
	mlx_hook(scene->mlx_window.win_ptr, ON_DESTROY, MASK_NO_EVENT, close_window,
		scene);
	mlx_hook(scene->mlx_window.win_ptr, ON_KEYDOWN, MASK_KEY_PRESS, key_hook,
		scene);
	mlx_hook(scene->mlx_window.win_ptr, ON_MOUSEDOWN, MASK_BUTTON_PRESS,
		mouse_hook, scene);
}
