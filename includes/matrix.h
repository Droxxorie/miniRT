/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:18:35 by eraad             #+#    #+#             */
/*   Updated: 2025/12/08 15:33:46 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <vector.h>

typedef enum e_mat_axis
{
	AXIS_RIGHT, // X axis
	AXIS_UP,   // Y axis
	AXIS_FORWARD, // Z axis
	AXIS_ORIGIN // Translation
}	t_mat_axis;

typedef struct s_mat4
{
	t_real	m[4][4];
}	t_mat4;

#endif