/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 09:26:34 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 10:48:40 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	translate_light(t_light *light, t_vec3 transation)
{
	t_mat4	translation_matrix;

	if (!light)
		return ;
	translation_matrix = make_translation_matrix(transation);
	light->position = apply_matrix_to_point3(translation_matrix,
			light->position);
}
