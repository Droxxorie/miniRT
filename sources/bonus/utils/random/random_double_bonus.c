/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_double_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:45:33 by eraad             #+#    #+#             */
/*   Updated: 2026/01/24 14:40:45 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	random_double(unsigned int *seed)
{
	*seed = pcg_hash(*seed);
	return ((t_real)(*seed) / (t_real)UINT_MAX);
}

//* pas thread safe
t_real	random_real(void)
{
	return ((t_real)rand() / (t_real)RAND_MAX + 1.0f);
}

//* pas thread safe
t_real	random_real_range(t_real min, t_real max)
{
	return (min + (max - min) * random_real());
}
