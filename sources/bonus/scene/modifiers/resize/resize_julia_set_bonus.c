/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_julia_set_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:59:02 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 14:02:20 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	change_cut(t_object *object, int direction)
{
	if (direction > 0)
		object->u_data.julia_set.cut = TRUE;
	else
		object->u_data.julia_set.cut = FALSE;
}

static void	change_orbital_trap(t_object *object, int direction)
{
	if (direction > 0)
		object->u_data.julia_set.orbital_trap = TRUE;
	else
		object->u_data.julia_set.orbital_trap = FALSE;
}

void	resize_julia_set(t_object *object, int mode, int direction)
{
	t_vec3		scale_factors;
	t_mat4		scale_matrix;
	t_real		factor;

	if (mode == RESIZE_X)
		return (change_cut(object, direction));
	else if (mode == RESIZE_Y)
		return (change_orbital_trap(object, direction));
	if (direction > 0)
		factor = 1.1;
	else
		factor = 0.9;
	scale_factors = (t_vec3){factor, factor, factor};
	scale_matrix = make_scale_matrix(scale_factors);
	object->transform = mat4_mult_mat4(object->transform, scale_matrix);
	set_transform(object, object->transform);
}
