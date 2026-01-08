/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sphere_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:40:42 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 17:40:51 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	update_sphere_matrix(t_object *object)
{
	t_mat4	translation;
	t_mat4	scaling;
	t_mat4	transform;

	translation = make_translation_matrix(object->u_data.sphere.center);
	scaling = make_scale_matrix((t_vec3){object->u_data.sphere.radius,
			object->u_data.sphere.radius, object->u_data.sphere.radius});
	transform = identity_matrix();
	transform = mat4_mult_mat4(transform, translation);
	transform = mat4_mult_mat4(transform, scaling);
	set_transform(object, transform);
}
