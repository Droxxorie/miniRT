/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_torus_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 20:43:18 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 20:44:10 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	reset_torus_state(t_object *object)
{
	t_torus	*torus;

	torus = &object->u_data.torus;
	torus->center = torus->initial_center;
	torus->axis = torus->initial_axis;
	torus->major_radius = torus->initial_major_radius;
	torus->minor_radius = torus->initial_minor_radius;
	update_object(object);
}
