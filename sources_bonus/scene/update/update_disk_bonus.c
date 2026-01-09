/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_disk_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:58:23 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 09:11:43 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	update_disk(t_object *obj)
{
	t_mat4	translation;
	t_mat4	rotation;
	t_mat4	scaling;
	t_mat4	transform;

	translation = make_translation_matrix(obj->u_data.disk.center);
	rotation = rotation_align(obj->u_data.disk.normal);
	scaling = make_scale_matrix((t_vec3){obj->u_data.disk.radius, 1.0,
			obj->u_data.disk.radius});
	transform = identity_matrix();
	transform = mat4_mult_mat4(transform, translation);
	transform = mat4_mult_mat4(transform, rotation);
	transform = mat4_mult_mat4(transform, scaling);
	set_transform(obj, transform);
}
