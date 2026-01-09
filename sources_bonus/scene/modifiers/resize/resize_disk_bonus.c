/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_disk_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:20:18 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 08:55:38 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_disk(t_object *object, int mode, int direction)
{
	t_disk	*disk;

	if (mode == RESIZE_X)
	{
		disk = &object->u_data.disk;
		disk->radius += (direction * STEP_SIZE);
		if (disk->radius < 0.1)
			disk->radius = 0.1;
		log_event(stdout, "INFO", "Disk radius resized to %.2f",
			disk->radius);
		update_object(object);
	}
}
