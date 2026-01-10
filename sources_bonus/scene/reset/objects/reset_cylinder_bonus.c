/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_cylinder_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:57:15 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 20:44:27 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	reset_cylinder_state(t_object *object)
{
	t_cylinder	*cylinder;

	cylinder = &object->u_data.cylinder;
	cylinder->center = cylinder->initial_center;
	cylinder->axis = cylinder->initial_axis;
	cylinder->radius = cylinder->initial_radius;
	cylinder->height = cylinder->initial_height;
	update_object(object);
}
