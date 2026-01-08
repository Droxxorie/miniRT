/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_cylinder_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:39:33 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 16:36:56 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	save_cylinder_state(t_cylinder *cylinder)
{
	cylinder->initial_center = cylinder->center;
	cylinder->initial_axis = cylinder->axis;
	cylinder->initial_radius = cylinder->radius;
	cylinder->initial_height = cylinder->height;
}
