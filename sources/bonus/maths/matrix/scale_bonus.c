/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:32:57 by eraad             #+#    #+#             */
/*   Updated: 2026/01/12 23:52:14 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	get_min_scale_factor(t_mat4 mat)
{
	t_vec3	scale;
	t_real	min;

	scale.x = vec3_len_squared((t_vec3){mat.m[0][0], mat.m[1][0], mat.m[2][0]});
	scale.y = vec3_len_squared((t_vec3){mat.m[0][1], mat.m[1][1], mat.m[2][1]});
	scale.z = vec3_len_squared((t_vec3){mat.m[0][2], mat.m[1][2], mat.m[2][2]});
	min = scale.x;
	if (scale.y < min)
		min = scale.y;
	if (scale.z < min)
		min = scale.z;
	if (min < EPSILON)
		return (EPSILON);
	return (sqrt(min));
}

t_mat4	make_scale_matrix(t_vec3 scale)
{
	t_mat4	mat;

	mat = identity_matrix();
	mat.m[0][0] = scale.x;
	mat.m[1][1] = scale.y;
	mat.m[2][2] = scale.z;
	return (mat);
}
