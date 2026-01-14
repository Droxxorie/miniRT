/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:09:29 by eraad             #+#    #+#             */
/*   Updated: 2026/01/15 00:00:28 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	init_fractal_matrix(t_object *object, t_point3 center, t_vec3 axis,
		t_real size)
{
	t_mat4	translation;
	t_mat4	rotation;
	t_mat4	scale;
	t_mat4	transform;

	translation = make_translation_matrix(center);
	rotation = rotation_align(axis);
	scale = make_scale_matrix((t_vec3){size, size, size});
	transform = identity_matrix();
	transform = mat4_mult_mat4(transform, translation);
	transform = mat4_mult_mat4(transform, rotation);
	transform = mat4_mult_mat4(transform, scale);
	set_transform(object, transform);
}
