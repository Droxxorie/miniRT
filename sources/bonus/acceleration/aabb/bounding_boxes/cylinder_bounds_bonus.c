/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bounds_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:32:38 by eraad             #+#    #+#             */
/*   Updated: 2026/01/19 13:56:25 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

t_aabb	compute_cylinder_bounds(void)
{
	t_aabb	box;

	box.min = (t_point3){-1.0, -1.0, -1.0};
	box.max = (t_point3){1.0, 1.0, 1.0};
	return (box);
}
