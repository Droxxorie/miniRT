/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:16:34 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 12:17:36 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	rotate_cylinder(t_object *object, t_vec3 rotation_axis)
{
	t_real	angle;
	t_vec3	axis;

	angle = vec3_length(rotation_axis);
	if (angle < EPSILON)
		return ;
	axis = vec3_normalize(rotation_axis);
	object->u_data.cylinder.axis = rotate_vector(object->u_data.cylinder.axis, axis, angle);
	update_object_matrix(object);
}
