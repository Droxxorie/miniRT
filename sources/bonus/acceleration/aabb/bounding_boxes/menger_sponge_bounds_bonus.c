/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menger_sponge_bounds_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:23:03 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 23:23:24 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_aabb	compute_menger_sponge_bounds(void)
{
	t_aabb	box;

	box.min = (t_point3){-1.1, -1.1, -1.1};
	box.max = (t_point3){1.1, 1.1, 1.1};
	return (box);
}
