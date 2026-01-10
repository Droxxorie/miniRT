/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_rectangle_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 19:42:52 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 15:59:05 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	translate_rectangle(t_object *object, t_vec3 translation)
{
	t_mat4	translation_matrix;

	if (!object)
		return ;
	translation_matrix = make_translation_matrix(translation);
	object->transform = mat4_mult_mat4(translation_matrix, object->transform);
	set_transform(object, object->transform);
}
