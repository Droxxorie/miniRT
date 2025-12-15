/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:41:02 by eraad             #+#    #+#             */
/*   Updated: 2025/12/15 14:41:41 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	translate_cylinder(t_object *object, t_vec3 translation)
{
	t_mat4	translation_matrix;

	translation_matrix = make_translation_matrix(translation);
	object->data.cylinder.center = mat4_mult_point(translation_matrix,
			object->data.cylinder.center);
}
