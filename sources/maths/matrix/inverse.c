/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:05:52 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 22:28:06 by eraad            ###   ########.fr       */
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

//* GAUSS JORDAN METHOD */

// /* Échange deux lignes dans la matrice et dans l'identité */
// static void	swap_rows(t_mat4 *m, t_mat4 *inv, int row1, int row2)
// {
// 	t_real	tmp;
// 	int		i;

// 	if (row1 == row2)
// 		return ;
// 	i = -1;
// 	while (++i < 4)
// 	{
// 		tmp = m->m[row1][i];
// 		m->m[row1][i] = m->m[row2][i];
// 		m->m[row2][i] = tmp;
// 		tmp = inv->m[row1][i];
// 		inv->m[row1][i] = inv->m[row2][i];
// 		inv->m[row2][i] = tmp;
// 	}
// }

// /* Divise la ligne du pivot pour avoir un 1 sur la diagonale */
// static void	normalize_row(t_mat4 *m, t_mat4 *inv, int r, t_real pivot)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < 4)
// 	{
// 		m->m[r][i] /= pivot;
// 		inv->m[r][i] /= pivot;
// 	}
// }

// /* Annule les coefficients de la colonne c pour les autres lignes */
// static void	eliminate_col(t_mat4 *m, t_mat4 *inv, int r, int c)
// {
// 	t_real	factor;
// 	int		k;

// 	factor = m->m[r][c];
// 	k = -1;
// 	while (++k < 4)
// 	{
// 		m->m[r][k] -= factor * m->m[c][k];
// 		inv->m[r][k] -= factor * inv->m[c][k];
// 	}
// }

// t_mat4	mat4_inverse(t_mat4 src)
// {
// 	t_mat4 inv;
// 	int i;
// 	int j;
// 	int pivot_idx;

// 	inv = identity_matrix();
// 	i = -1;
// 	while (++i < 4)
// 	{
// 		/* 1. Trouver le pivot (le plus grand absolu dans la colonne) */
// 		pivot_idx = i;
// 		j = i;
// 		while (++j < 4)
// 			if (fabs(src.m[j][i]) > fabs(src.m[pivot_idx][i]))
// 				pivot_idx = j;

// 		/* 2. Si le pivot est proche de 0, la matrice n'est pas inversible */
// 		if (fabs(src.m[pivot_idx][i]) < EPSILON)
// 			return (identity_matrix()); // Ou gestion d'erreur

// 		/* 3. Swap & Normalize */
// 		swap_rows(&src, &inv, i, pivot_idx);
// 		normalize_row(&src, &inv, i, src.m[i][i]);

// 		/* 4. Elimination Gaussienne */
// 		j = -1;
// 		while (++j < 4)
// 			if (j != i)
// 				eliminate_col(&src, &inv, j, i);
// 	}
// 	return (inv);
// }
