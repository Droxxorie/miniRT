/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object_to_scene_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:44:42 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:42:10 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	add_object_to_scene(t_scene *scene, t_object *new_object)
{
	t_object	*current;

	if (scene->objects == NULL)
		scene->objects = new_object;
	else
	{
		current = scene->objects;
		while (current->next)
			current = current->next;
		current->next = new_object;
	}
}
