/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:55:33 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 19:32:46 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static int	key_release_hook(int key, t_scene *scene)
{
	if (key == KEY_SHIFT_L || key == KEY_SHIFT_R)
		scene->shift_pressed = FALSE;
	else if (key == KEY_CTRL_L || key == KEY_CTRL_R)
		scene->ctrl_pressed = FALSE;
	return (0);
}

static int	close_window(t_scene *scene)
{
	ft_putendl_fd("", STDOUT_FILENO);
	clean_exit(scene, EXIT_SUCCESS);
	return (0);
}

void	input_manager(t_scene *scene)
{
	if (!scene || !scene->mlx_window.mlx_ptr || !scene->mlx_window.win_ptr)
		return ;
	mlx_hook(scene->mlx_window.win_ptr, ON_DESTROY, MASK_NO_EVENT, close_window,
		scene);
	mlx_hook(scene->mlx_window.win_ptr, ON_KEYDOWN, MASK_KEY_PRESS, key_hook,
		scene);
	mlx_hook(scene->mlx_window.win_ptr, ON_KEYUP, MASK_KEY_RELEASE,
		key_release_hook, scene);
	mlx_hook(scene->mlx_window.win_ptr, ON_MOUSEDOWN, MASK_BUTTON_PRESS,
		mouse_hook, scene);
}
