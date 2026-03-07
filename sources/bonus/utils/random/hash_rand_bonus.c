/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_rand_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:45:21 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 17:46:49 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	hash_rand(t_point3 p, int seed)
{
	t_real	magic_number;
	t_vec3	magic_vector;
	t_real	dot_result;

	magic_vector = (t_vec3){12.9898, 78.233, 45.719};
	magic_number = 43758.5453;
	dot_result = vec3_dot(p, magic_vector);
	dot_result += (t_real)seed * 0.1571;
	return (sinf(dot_result) * magic_number - (int)(sinf(dot_result)
		* magic_number));
}

unsigned int	pcg_hash(unsigned int input)
{
	unsigned int	state;
	unsigned int	word;

	state = input * 747796405u + 2891336453u;
	word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
	return ((word >> 22u) ^ word);
}
