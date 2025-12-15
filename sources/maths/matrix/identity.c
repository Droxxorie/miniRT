/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:41:26 by eraad             #+#    #+#             */
/*   Updated: 2025/12/15 14:07:50 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_mat4	identity_matrix(void)
{
	t_mat4	identity;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				identity.m[i][j] = 1.0;
			else
				identity.m[i][j] = 0.0;
			j++;
		}
		i++;
	}
	return (identity);
}
