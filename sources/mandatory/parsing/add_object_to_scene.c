/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object_to_scene.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:44:42 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 12:28:29 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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
