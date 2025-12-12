/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:52:04 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 18:53:17 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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

static int	get_camera_count(t_camera *cameras)
{
	int count;

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

	count = 0;
	while (objects)
	{
		count++;
		objects = objects->next;
	}
	return (count);
}
