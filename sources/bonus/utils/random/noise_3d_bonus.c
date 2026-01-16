/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_3d_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:45:21 by eraad             #+#    #+#             */
/*   Updated: 2026/01/15 17:58:30 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	noise_3d(t_point3 p)
{
	t_real	magic_number;
	t_vec3	magic_vector;
	t_real	magic_value;

	magic_vector = (t_vec3){12.9898, 78.233, 45.719};
	magic_number = 43758.5453;
	magic_value = vec3_dot(p, magic_vector);
	return (sin(magic_value) * magic_number - (int)(sin(magic_value)
		* magic_number));
}
