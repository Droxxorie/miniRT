/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_torus_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 20:46:21 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 17:09:08 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_torus(t_object *object, int mode, int direction)
{
	t_torus	*torus;
	t_real	factor;

	torus = &object->u_data.torus;
	if (direction > 0)
		factor = 1.1;
	else
		factor = 0.9;
	if (mode == RESIZE_X)
		torus->major_radius *= factor;
	else if (mode == RESIZE_Y)
		torus->minor_radius *= factor;
	else
		return ;
	torus->major_radius_sq = torus->major_radius * torus->major_radius;
	torus->minor_radius_sq = torus->minor_radius * torus->minor_radius;
	torus->diff_radius_sq = torus->major_radius_sq - torus->minor_radius_sq;
	log_event(stdout, "INFO", "Torus resized");
}
