/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set_bounds_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 13:38:02 by eraad             #+#    #+#             */
/*   Updated: 2026/01/18 14:08:38 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_aabb	compute_julia_set_bounds(void)
{
	t_aabb	box;

	box.min = (t_point3){-2.5, -2.5, -2.5};
	box.max = (t_point3){2.5, 2.5, 2.5};
	return (box);
}
