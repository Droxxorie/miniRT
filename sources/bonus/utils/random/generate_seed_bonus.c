/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_seed_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:42:14 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 18:59:56 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static unsigned int	bit_cast_double_to_uint(t_real d)
{
	unsigned int	result;

	memcpy(&result, &d, sizeof(t_real));
	return (result);
}

unsigned int	generate_seed(t_point3 p)
{
	unsigned int	seed;

	seed = pcg_hash(bit_cast_double_to_uint(p.x));
	seed = pcg_hash(seed ^ bit_cast_double_to_uint(p.y));
	seed = pcg_hash(seed ^ bit_cast_double_to_uint(p.z));
	return (seed);
}
