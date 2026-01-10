/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_triangle_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 22:38:19 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 20:02:17 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	translate_triangle(t_object *object, t_vec3 translation)
{
	t_mat4	translation_matrix;

	if (!object)
		return ;
	translation_matrix = make_translation_matrix(translation);
	object->transform = mat4_mult_mat4(translation_matrix, object->transform);
	set_transform(object, object->transform);
}
