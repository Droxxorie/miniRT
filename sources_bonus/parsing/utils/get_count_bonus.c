/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_count_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:52:04 by eraad             #+#    #+#             */
/*   Updated: 2026/01/11 17:57:01 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

int	get_light_count(t_light *lights)
{
	int	count;

	count = 0;
	while (lights)
	{
		count++;
		lights = lights->next;
	}
	return (count);
}

int	get_camera_count(t_camera *cameras)
{
	int	count;

	count = 0;
	while (cameras)
	{
		count++;
		cameras = cameras->next;
	}
	return (count);
}

int	get_object_count(t_object *objects)
{
	int	count;

	if (!objects)
		return (-1);
	count = 0;
	while (objects)
	{
		count++;
		objects = objects->next;
	}
	return (count);
}
