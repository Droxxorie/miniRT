/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:09:37 by eraad             #+#    #+#             */
/*   Updated: 2026/01/21 21:24:21 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	free_objects(t_object *object)
{
	t_object	*temp;

	while (object)
	{
		temp = object->next;
		free(object);
		object = temp;
	}
}

void	free_lights(t_light *light)
{
	t_light	*temp;

	while (light)
	{
		temp = light->next;
		free(light);
		light = temp;
	}
}

void	free_cameras(t_camera *camera)
{
	t_camera	*temp;

	while (camera)
	{
		temp = camera->next;
		free(camera);
		camera = temp;
	}
}
