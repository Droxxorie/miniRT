/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_plane_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:40:17 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 17:40:28 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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
