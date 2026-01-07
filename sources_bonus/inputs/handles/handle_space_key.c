/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:28:40 by eraad             #+#    #+#             */
/*   Updated: 2026/01/07 00:45:34 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_bool	handle_space_key(t_scene *scene)
{
	if (scene->selected_light && scene->lights->next)
	{
		switch_light_next(scene);
		return (FALSE);
	}
	if (!scene->selected_object && scene->cameras->next)
	{
		switch_camera_next(scene);
		return (TRUE);
	}
	return (FALSE);
}
