/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:39:41 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 19:12:02 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	translate_plane(t_object *object, t_vec3 translation)
{
	t_mat4	translation_matrix;

	translation_matrix = make_translation_matrix(translation);
	object->u_data.plane.origin = mat4_mult_point(translation_matrix,
			object->u_data.plane.origin);
	object->u_data.plane.d = -vec3_dot(object->u_data.plane.normal,
			object->u_data.plane.origin);
}
