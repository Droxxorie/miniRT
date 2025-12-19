/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:16:34 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 22:48:22 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	rotate_cylinder(t_object *object, t_vec3 rotation_axis)
{
	t_real	angle;
	t_vec3	axis;

	angle = vec3_len(rotation_axis);
	if (angle < EPSILON)
		return ;
	axis = vec3_normalize(rotation_axis);
	object->u_data.cylinder.axis = rotate_vector(object->u_data.cylinder.axis,
			axis, angle);
	object->u_data.cylinder.axis = vec3_normalize(object->u_data.cylinder.axis);
	update_object_matrix(object);
}
