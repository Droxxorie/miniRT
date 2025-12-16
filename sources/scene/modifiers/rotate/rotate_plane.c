/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:06:18 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 11:06:20 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	rotate_plane(t_object *object, t_vec3 angles)
{
	t_mat4	rotation_matrix;

	rotation_matrix = make_rotation_matrix(angles);
	object->data.plane.normal = mat3_mult_vec3(rotation_matrix,
			object->data.plane.normal);
}
