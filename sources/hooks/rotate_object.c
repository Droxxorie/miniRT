/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:50:44 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 22:53:49 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	rotate_object(t_object *object, t_vec3 rot_axis)
{
	t_vec3	*axis_to_rotate;

	if (!object || object->type == SPHERE)
		return ;
	if (object->type == PLANE)
		axis_to_rotate = &object->data.plane.normal;
	else if (object->type == CYLINDER)
		axis_to_rotate = &object->data.cylinder.axis;
	else
		return ;
	*axis_to_rotate = vec3_add(*axis_to_rotate, vec3_scale(rot_axis, STEP_ROT));
	*axis_to_rotate = vec3_normalize(*axis_to_rotate);
}
