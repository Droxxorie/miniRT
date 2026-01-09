/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cylinder_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:41:01 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 09:11:39 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	update_cylinder(t_object *object)
{
	t_mat4	translation;
	t_mat4	rotation;
	t_mat4	scaling;
	t_mat4	transform;

	translation = make_translation_matrix(object->u_data.cylinder.center);
	rotation = rotation_align(object->u_data.cylinder.axis);
	scaling = make_scale_matrix((t_vec3){object->u_data.cylinder.radius,
			object->u_data.cylinder.height, object->u_data.cylinder.radius});
	transform = identity_matrix();
	transform = mat4_mult_mat4(transform, translation);
	transform = mat4_mult_mat4(transform, rotation);
	transform = mat4_mult_mat4(transform, scaling);
	set_transform(object, transform);
}
