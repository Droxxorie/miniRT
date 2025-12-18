/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:05:52 by eraad             #+#    #+#             */
/*   Updated: 2025/12/18 22:26:53 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_real	get_determinant(t_real mat[3][3])
{
	return (mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2]
			* mat[2][1]) + mat[0][1] * (mat[1][2] * mat[2][0]
			- mat[1][0] * mat[2][2]) + mat[0][2] * (mat[1][0]
			* mat[2][1] - mat[1][1] * mat[2][0]));
}

static t_real	get_cofactor(t_mat4 mat, int row, int col)
{
	t_real	sub_mat[3][3];
	t_real	determinant;
	int		i;
	int		j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			sub_mat[i][j] = mat.m[i + (i >= row)][j + (j >= col)];
	}
	determinant = get_determinant(sub_mat);
	if (((row + col) % 2) != 0)
		determinant = -determinant;
	return (determinant);
}

t_mat4	mat4_inverse(t_mat4 mat)
{
	t_mat4	inverse;
	t_real	determinant;
	int		i;
	int		j;

	determinant = 0;
	i = -1;
	while (++i < 4)
		determinant += mat.m[0][i] * get_cofactor(mat, 0, i);
	if (determinant == 0)
		return (identity_matrix());
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			inverse.m[j][i] = get_cofactor(mat, i, j) / determinant;
	}
	return (inverse);
}
