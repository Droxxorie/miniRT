/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_mandelbox_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:00:44 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 14:02:04 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_mandelbox(t_object *object, int mode, int direction)
{
	t_vec3	scale_factors;
	t_mat4	scale_matrix;
	t_real	factor;

	(void)mode;
	if (direction > 0)
		factor = 1.1;
	else
		factor = 0.9;
	scale_factors = (t_vec3){factor, factor, factor};
	scale_matrix = make_scale_matrix(scale_factors);
	object->transform = mat4_mult_mat4(object->transform, scale_matrix);
	set_transform(object, object->transform);
}
