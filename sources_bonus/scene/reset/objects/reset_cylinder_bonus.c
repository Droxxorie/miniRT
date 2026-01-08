/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_cylinder_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:57:15 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 23:40:56 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	reset_cylinder_state(t_object *object)
{
	object->u_data.cylinder.center = object->u_data.cylinder.initial_center;
	object->u_data.cylinder.axis = object->u_data.cylinder.initial_axis;
	object->u_data.cylinder.radius = object->u_data.cylinder.initial_radius;
	object->u_data.cylinder.height = object->u_data.cylinder.initial_height;
	update_object_matrix(object);
}
