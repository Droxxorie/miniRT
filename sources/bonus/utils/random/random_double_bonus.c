/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_double_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:45:33 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 17:51:03 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_real	random_double(unsigned int *seed)
{
	*seed = pcg_hash(*seed);
	return ((t_real)(*seed) / (t_real)UINT_MAX);
}
