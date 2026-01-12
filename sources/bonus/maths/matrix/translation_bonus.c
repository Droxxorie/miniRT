/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:11:00 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:40:48 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_mat4	make_translation_matrix(t_vec3 translation)
{
	t_mat4	mat;

	mat = identity_matrix();
	mat.m[0][3] = translation.x;
	mat.m[1][3] = translation.y;
	mat.m[2][3] = translation.z;
	return (mat);
}
