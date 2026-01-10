/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_disk_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:20:18 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 20:01:22 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_disk(t_object *object, int mode, int direction)
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
	else
		return ;
	scale_matrix = make_scale_matrix(scale_factors);
	object->transform = mat4_mult_mat4(object->transform, scale_matrix);
	set_transform(object, object->transform);
	log_event(stdout, "INFO", "Disk resized");
}
