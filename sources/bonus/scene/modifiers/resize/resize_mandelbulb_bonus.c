/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_mandelbulb_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:14:48 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 14:00:59 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	resize_power(t_object *object, int direction)
{
	t_real	factor;

	if (direction > 0)
		factor = 1;
	else
		factor = -1;
	object->u_data.mandelbulb.power += factor;
	if (object->u_data.mandelbulb.power < 2.0)
		object->u_data.mandelbulb.power = 2.0;
}

void	resize_mandelbulb(t_object *object, int mode, int direction)
{
	t_vec3	scale_factors;
	t_mat4	scale_matrix;
	t_real	factor;

	if (mode == RESIZE_X)
		return (resize_power(object, direction));
	if (direction > 0)
		factor = 1.1;
	else
		factor = 0.9;
	scale_factors = (t_vec3){factor, factor, factor};
	scale_matrix = make_scale_matrix(scale_factors);
	object->transform = mat4_mult_mat4(object->transform, scale_matrix);
	set_transform(object, object->transform);
}
