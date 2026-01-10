/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_cone_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 20:50:42 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 20:51:44 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_cone(t_object *object, int mode, int direction)
{
	t_vec3	scale_factors;
	t_mat4	scale_matrix;
	t_real	factor;

	if (direction > 0)
		factor = 1.1;
	else
		factor = 0.9;
	if (mode == RESIZE_X)
		scale_factors = (t_vec3){factor, 1.0, factor};
	else if (mode == RESIZE_Y)
		scale_factors = (t_vec3){1.0, factor, 1.0};
	else
		return ;
	scale_matrix = make_scale_matrix(scale_factors);
	object->transform = mat4_mult_mat4(object->transform, scale_matrix);
	set_transform(object, object->transform);
	log_event(stdout, "INFO", "Cone resized");
}
