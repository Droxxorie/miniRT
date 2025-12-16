/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:33:23 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 19:12:10 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	translate_sphere(t_object *object, t_vec3 translation)
{
	t_mat4	translation_matrix;

	translation_matrix = make_translation_matrix(translation);
	object->u_data.sphere.center = mat4_mult_point(translation_matrix,
			object->u_data.sphere.center);
}
