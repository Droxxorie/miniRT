/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 08:23:58 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 10:48:35 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	translate_camera(t_camera *camera, t_vec3 translation,
		t_real aspect_ratio)
{
	t_mat4	translation_matrix;

	if (!camera)
		return ;
	translation_matrix = make_translation_matrix(translation);
	camera->position = mat4_mult_point3(translation_matrix, camera->position);
	setup_camera(camera, aspect_ratio);
}
