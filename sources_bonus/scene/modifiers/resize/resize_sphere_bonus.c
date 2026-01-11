/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_sphere_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:18:57 by eraad             #+#    #+#             */
/*   Updated: 2026/01/11 15:01:51 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_sphere(t_object *object, int mode, int direction)
{
	t_real	factor;
	t_vec3	scale_factors;
	t_mat4	scale_matrix;

	if (direction > 0)
		factor = 1.1;
	else
		factor = 0.9;
	if (mode == RESIZE_UNIFORM)
		scale_factors = (t_vec3){factor, factor, factor};
	else if (mode == RESIZE_X)
		scale_factors = (t_vec3){factor, 1.0, 1.0};
	else if (mode == RESIZE_Y)
		scale_factors = (t_vec3){1.0, factor, 1.0};
	else if (mode == RESIZE_Z)
		scale_factors = (t_vec3){1.0, 1.0, factor};
	else
		return ;
	scale_matrix = make_scale_matrix(scale_factors);
	object->transform = mat4_mult_mat4(object->transform, scale_matrix);
	set_transform(object, object->transform);
	log_event(stdout, "INFO", "Sphere resized");
}
