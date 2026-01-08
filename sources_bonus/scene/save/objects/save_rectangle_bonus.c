/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_rectangle_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:48:31 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 20:49:01 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	save_rectangle_state(t_rectangle *rectangle)
{
	rectangle->initial_center = rectangle->center;
	rectangle->initial_normal = rectangle->normal;
	rectangle->initial_width = rectangle->width;
	rectangle->initial_height = rectangle->height;
}
