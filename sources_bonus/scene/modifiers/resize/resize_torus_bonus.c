/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_torus_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 20:46:21 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 20:48:46 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_torus(t_object *object, int mode, int direction)
{
	t_torus	*torus;
	t_real	change;

	torus = &object->u_data.torus;
	change = direction * STEP_SIZE;
	if (mode == RESIZE_X)
	{
		torus->major_radius += change;
		if (torus->major_radius < 0.1)
			torus->major_radius = 0.1;
		log_event(stdout, "INFO", "Torus major radius resized to %.2f",
			torus->major_radius);
		update_object(object);
	}
	else if (mode == RESIZE_Y)
	{
		torus->minor_radius += change;
		if (torus->minor_radius < 0.1)
			torus->minor_radius = 0.1;
		log_event(stdout, "INFO", "Torus minor radius resized to %.2f",
			torus->minor_radius);
		update_object(object);
	}
}
