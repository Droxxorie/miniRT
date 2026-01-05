/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_t_key_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 22:55:18 by eraad             #+#    #+#             */
/*   Updated: 2026/01/06 00:20:17 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	handle_t_key(t_scene *scene)
{
	if (scene->selected_object)
		scene->selected_object->visible = !scene->selected_object->visible;
	else if (scene->selected_light)
		scene->selected_light->active = !scene->selected_light->active;
}
