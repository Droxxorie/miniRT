/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_light_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:22:49 by eraad             #+#    #+#             */
/*   Updated: 2026/01/22 19:51:59 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_mat4	make_rotation_matrix(t_real angle, t_vec3 axis)
{
	t_mat4	mat;
	t_real	cosine;
	t_real	sine;
	t_real	o_m_c;

	mat = identity_matrix();
	cosine = cos(angle);
	sine = sin(angle);
	o_m_c = 1.0 - cosine;
	axis = vec3_normalize(axis);
	mat.m[0][0] = axis.x * axis.x * o_m_c + cosine;
	mat.m[0][1] = axis.x * axis.y * o_m_c - axis.z * sine;
	mat.m[0][2] = axis.x * axis.z * o_m_c + axis.y * sine;
	mat.m[1][0] = axis.y * axis.x * o_m_c + axis.z * sine;
	mat.m[1][1] = axis.y * axis.y * o_m_c + cosine;
	mat.m[1][2] = axis.y * axis.z * o_m_c - axis.x * sine;
	mat.m[2][0] = axis.z * axis.x * o_m_c - axis.y * sine;
	mat.m[2][1] = axis.z * axis.y * o_m_c + axis.x * sine;
	mat.m[2][2] = axis.z * axis.z * o_m_c + cosine;
	return (mat);
}

void	rotate_light(t_light *light, t_camera *camera, t_vec3 axis)
{
	t_mat4	rotation_matrix;
	t_real	angle;

	if (!light || light->type == LIGHT_POINT)
		return ;
	angle = ROT_SPEED * camera->scale_factor;
	rotation_matrix = make_rotation_matrix(angle, axis);
	light->direction = mat4_mult_vec3(rotation_matrix, light->direction);
	light->direction = vec3_normalize(light->direction);
	if (light->type == LIGHT_QUAD)
	{
		light->u = mat4_mult_vec3(rotation_matrix, light->u);
		light->v = mat4_mult_vec3(rotation_matrix, light->v);
	}
}
