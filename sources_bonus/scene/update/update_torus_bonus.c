/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_torus_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:38:12 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 01:06:23 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	update_torus(t_object *object)
{
	t_mat4	translation;
	t_mat4	rotation;
	t_mat4	transform;
	t_torus	*torus;

	torus = &object->u_data.torus;
	torus->major_radius_sq = torus->major_radius * torus->major_radius;
	torus->minor_radius_sq = torus->minor_radius * torus->minor_radius;
	torus->diff_radius_sq = torus->major_radius_sq - torus->minor_radius_sq;
	translation = make_translation_matrix(torus->center);
	rotation = rotation_align(torus->axis);
	transform = identity_matrix();
	transform = mat4_mult_mat4(transform, translation);
	transform = mat4_mult_mat4(transform, rotation);
	set_transform(object, transform);
}
