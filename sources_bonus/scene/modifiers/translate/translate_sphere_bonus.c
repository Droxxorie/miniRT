/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_sphere_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:33:23 by eraad             #+#    #+#             */
/*   Updated: 2026/01/10 20:02:13 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	translate_sphere(t_object *object, t_vec3 translation_vector)
{
	t_mat4	translation_matrix;

	translation_matrix = make_translation_matrix(translation_vector);
	object->transform = mat4_mult_mat4(translation_matrix, object->transform);
	set_transform(object, object->transform);
}
