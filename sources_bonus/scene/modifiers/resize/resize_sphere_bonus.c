/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_sphere_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:18:57 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 20:01:39 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	resize_sphere(t_object *object, int mode, int direction)
{
	t_real	scale_factor;
	t_mat4	scale_matrix;

	if (mode == RESIZE_X)
	{
		if (direction > 0)
			scale_factor = 1.1;
		else
			scale_factor = 0.9;
		scale_matrix = make_scale_matrix((t_vec3){scale_factor, scale_factor,
				scale_factor});
		object->transform = mat4_mult_mat4(object->transform, scale_matrix);
		set_transform(object, object->transform);
		log_event(stdout, "INFO", "Sphere resized");
	}
}
