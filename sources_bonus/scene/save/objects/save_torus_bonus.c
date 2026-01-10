/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_torus_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 20:40:56 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 20:42:12 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	save_torus_state(t_torus *torus)
{
	torus->initial_center = torus->center;
	torus->initial_axis = torus->axis;
	torus->initial_major_radius = torus->major_radius;
	torus->initial_minor_radius = torus->minor_radius;
}
