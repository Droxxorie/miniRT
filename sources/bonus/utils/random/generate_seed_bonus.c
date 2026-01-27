/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_seed_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:42:14 by eraad             #+#    #+#             */
/*   Updated: 2026/01/26 21:12:32 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static unsigned int	bit_cast_double_to_uint(t_real d)
{
	unsigned int	result;
	size_t			len;

	if (sizeof(t_real) < sizeof(unsigned int))
		len = sizeof(t_real);
	else
		len = sizeof(unsigned int);
	result = 0;
	memcpy(&result, &d, len);
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
