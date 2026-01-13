/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbox_bounds_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:22:19 by eraad             #+#    #+#             */
/*   Updated: 2026/01/13 23:22:48 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_aabb	compute_mandelbox_bounds(void)
{
	t_aabb	box;

	box.min = (t_point3){-4.0, -4.0, -4.0}; //a voir avec le scale
	box.max = (t_point3){4.0, 4.0, 4.0};
	return (box);
}
