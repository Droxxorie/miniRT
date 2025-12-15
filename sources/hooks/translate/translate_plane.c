/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:39:41 by eraad             #+#    #+#             */
/*   Updated: 2025/12/15 14:40:40 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	translate_plane(t_object *object, t_vec3 translation)
{
	t_mat4	translation_matrix;

	translation_matrix = make_translation_matrix(translation);
	object->data.plane.origin = mat4_mult_point(translation_matrix,
			object->data.plane.origin);
	object->data.plane.d = -vec3_dot(object->data.plane.normal,
			object->data.plane.origin);
}
