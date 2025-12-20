/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:41:45 by eraad             #+#    #+#             */
/*   Updated: 2025/12/20 19:04:50 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec3	mat4_mult_point3(t_mat4 mat, t_point3 pt)
{
	t_vec3	result;

	result.x = mat.m[0][0] * pt.x + mat.m[0][1] * pt.y + mat.m[0][2] * pt.z
		+ mat.m[0][3];
	result.y = mat.m[1][0] * pt.x + mat.m[1][1] * pt.y + mat.m[1][2] * pt.z
		+ mat.m[1][3];
	result.z = mat.m[2][0] * pt.x + mat.m[2][1] * pt.y + mat.m[2][2] * pt.z
		+ mat.m[2][3];
	return (result);
}

t_vec3	mat4_mult_vec3(t_mat4 mat, t_vec3 vec)
{
	t_vec3	result;

	result.x = mat.m[0][0] * vec.x + mat.m[0][1] * vec.y + mat.m[0][2] * vec.z;
	result.y = mat.m[1][0] * vec.x + mat.m[1][1] * vec.y + mat.m[1][2] * vec.z;
	result.z = mat.m[2][0] * vec.x + mat.m[2][1] * vec.y + mat.m[2][2] * vec.z;
	return (result);
}

t_mat4	mat4_mult_mat4(t_mat4 a, t_mat4 b)
{
	t_mat4	result;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.m[i][j] = 0;
			k = 0;
			while (k < 4)
			{
				result.m[i][j] += a.m[i][k] * b.m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}
