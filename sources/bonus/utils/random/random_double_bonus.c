/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_double_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:45:33 by eraad             #+#    #+#             */
/*   Updated: 2026/01/20 18:34:44 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	random_double(unsigned int *seed)
{
	*seed = pcg_hash(*seed);
	return ((t_real)(*seed) / (t_real)UINT_MAX);
}

t_real	random_real(void)
{
	return (rand() / (t_real)RAND_MAX + 1.0);
}

t_real	random_real_range(t_real min, t_real max)
{
	return (min + (max - min) * random_real());
}
