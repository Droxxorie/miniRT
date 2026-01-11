/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle_bounds_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:34:39 by eraad             #+#    #+#             */
/*   Updated: 2026/01/11 21:35:48 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_aabb	compute_rectangle_bounds(void)
{
	t_aabb	box;

	box.min = (t_point3){-0.5, -EPSILON, -0.5};
	box.max = (t_point3){0.5, EPSILON, 0.5};
	return (box);
}
