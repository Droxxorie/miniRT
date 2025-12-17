/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 08:27:57 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 18:22:28 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	rotate_camera(t_camera *camera, t_vec3 angles, t_real aspect_ratio)
{
	t_mat4	rotation_matrix;

	if (!camera)
		return ;
	rotation_matrix = make_rotation_matrix(angles);
	camera->direction = vec3_normalize(mat3_mult_vec3(rotation_matrix,
				camera->direction));
	setup_camera(camera, aspect_ratio);
}
