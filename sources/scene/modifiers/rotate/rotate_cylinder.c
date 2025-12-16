/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:16:34 by eraad             #+#    #+#             */
/*   Updated: 2025/12/15 14:38:43 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	rotate_cylinder(t_object *object, t_vec3 angles)
{
	t_mat4	rotation_matrix;

	rotation_matrix = make_rotation_matrix(angles);
	object->data.cylinder.axis = mat3_mult_vec3(rotation_matrix,
			object->data.cylinder.axis);
}
