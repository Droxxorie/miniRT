/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_c_key_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 12:58:23 by eraad             #+#    #+#             */
/*   Updated: 2026/01/04 12:58:51 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	handle_c_key(t_scene *scene)
{
	if (scene->selected_object != NULL || scene->selected_light != NULL)
	{
		scene->selected_object = NULL;
		scene->selected_light = NULL;
		ft_putstr_fd("Switched to camera control mode\n", 1);
		ft_putstr_fd("Camera ID: ", 1);
		ft_putnbr_fd(scene->active_camera->id, 1);
		ft_putstr_fd("\n", 1);
	}
}
