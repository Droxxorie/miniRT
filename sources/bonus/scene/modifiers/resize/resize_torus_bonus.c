/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_torus_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 20:46:21 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 17:31:34 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_torus(t_object *object, t_camera *camera, int mode,
		int direction)
{
	t_torus	*torus;
	t_real	factor;
	t_real	intensity;

	intensity = camera->scale_factor * RESIZE_SPEED;
	if (direction > 0)
		factor = 1.0 + intensity;
	else
		factor = 1.0 - intensity;
	torus = &object->u_data.torus;
	if (mode == RESIZE_X)
		torus->major_radius *= factor;
	else if (mode == RESIZE_Y || mode == RESIZE_Z)
		torus->minor_radius *= factor;
	else if (mode == RESIZE_UNIFORM)
	{
		torus->major_radius *= factor;
		torus->minor_radius *= factor;
	}
	else
		return ;
	torus->major_radius_sq = torus->major_radius * torus->major_radius;
	torus->minor_radius_sq = torus->minor_radius * torus->minor_radius;
	torus->diff_radius_sq = torus->major_radius_sq - torus->minor_radius_sq;
}
