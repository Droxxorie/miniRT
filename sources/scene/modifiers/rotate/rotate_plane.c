/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:06:18 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 19:14:34 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	rotate_plane(t_object *object, t_vec3 rotation_axis)
{
	t_real	angle;
	t_vec3	axis;

	angle = vec3_len(rotation_axis);
	if (angle < EPSILON)
		return ;
	axis = vec3_normalize(rotation_axis);
	object->u_data.plane.normal = rotate_vector(object->u_data.plane.normal, axis, angle);
	object->u_data.plane.normal = vec3_normalize(object->u_data.plane.normal);
	update_object_matrix(object);
}
