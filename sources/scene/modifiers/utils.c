/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 22:32:33 by eraad             #+#    #+#             */
/*   Updated: 2025/12/20 19:07:48 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	set_transform(t_object *object, t_mat4 transform)
{
	if (!object)
		return ;
	object->transform = transform;
	object->inverse = mat4_inverse(object->transform);
	object->transposed_inverse = mat4_transpose(object->inverse);
}

void	apply_rotation_to_matrix(t_object *object, t_mat4 rotation_matrix)
{
	t_point3	position;
	t_mat4		old_transform;

	position.x = object->transform.m[0][3];
	position.y = object->transform.m[1][3];
	position.z = object->transform.m[2][3];
	old_transform = object->transform;
	old_transform.m[0][3] = 0.0;
	old_transform.m[1][3] = 0.0;
	old_transform.m[2][3] = 0.0;
	object->transform = mat4_mult_mat4(rotation_matrix, old_transform);
	object->transform.m[0][3] = position.x;
	object->transform.m[1][3] = position.y;
	object->transform.m[2][3] = position.z;
	set_transform(object, object->transform);
}
