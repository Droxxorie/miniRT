/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_menger_sponge_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:54:35 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 17:31:27 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	resize_scale_factor(t_object *object, int direction)
{
	t_real	factor;

	if (direction > 0)
		factor = 0.1;
	else
		factor = -0.1;
	object->u_data.menger_sponge.scale_factor += factor;
	if (object->u_data.menger_sponge.scale_factor < 1.3)
		object->u_data.menger_sponge.scale_factor = 1.3;
	else if (object->u_data.menger_sponge.scale_factor > 5.0)
		object->u_data.menger_sponge.scale_factor = 5.0;
}

void	resize_menger_sponge(t_object *object, t_camera *camera, int mode,
		int direction)
{
	t_vec3	scale_factors;
	t_mat4	scale_matrix;
	t_real	factor;
	t_real	intensity;

	if (mode == RESIZE_X)
		return (resize_scale_factor(object, direction));
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
