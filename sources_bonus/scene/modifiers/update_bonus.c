/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:37:28 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:44:16 by eraad            ###   ########.fr       */
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

void	update_plane_matrix(t_object *object)
{
	t_mat4	translation;
	t_mat4	rotation;
	t_mat4	transform;

	translation = make_translation_matrix(object->u_data.plane.origin);
	rotation = rotation_align(object->u_data.plane.normal);
	transform = identity_matrix();
	transform = mat4_mult_mat4(transform, translation);
	transform = mat4_mult_mat4(transform, rotation);
	set_transform(object, transform);
}

void	update_cylinder_matrix(t_object *object)
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

void	update_object_matrix(t_object *object)
{
	if (object->type == SPHERE)
		update_sphere_matrix(object);
	else if (object->type == PLANE)
		update_plane_matrix(object);
	else if (object->type == CYLINDER)
		update_cylinder_matrix(object);
}
