/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_rectangle_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:41:33 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 20:41:44 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	update_rectangle_matrix(t_object *object)
{
	t_mat4	translation;
	t_mat4	rotation;
	t_mat4	scaling;
	t_mat4	transform;

	translation = make_translation_matrix(object->u_data.rectangle.center);
	rotation = rotation_align(object->u_data.rectangle.normal);
	scaling = make_scale_matrix((t_vec3){object->u_data.rectangle.width, 1.0,
			object->u_data.rectangle.height});
	transform = identity_matrix();
	transform = mat4_mult_mat4(transform, translation);
	transform = mat4_mult_mat4(transform, rotation);
	transform = mat4_mult_mat4(transform, scaling);
	set_transform(object, transform);
}
