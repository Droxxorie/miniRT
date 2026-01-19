/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_mandelbox_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:00:44 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 12:45:39 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_mandelbox(t_object *object, t_camera *camera, int mode,
		int direction)
{
	t_vec3	scale_factors;
	t_mat4	scale_matrix;
	t_real	factor;
	t_real	intensity;

	(void)mode;
	intensity = camera->scale_factor * RESIZE_SPEED;
	if (direction > 0)
		factor = 1.0 + intensity;
	else
		factor = 1.0 - intensity;
	scale_factors = (t_vec3){factor, factor, factor};
	scale_matrix = make_scale_matrix(scale_factors);
	object->transform = mat4_mult_mat4(object->transform, scale_matrix);
	set_transform(object, object->transform);
}
