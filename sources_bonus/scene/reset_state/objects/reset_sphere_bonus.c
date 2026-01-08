/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_sphere_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:56:49 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 13:06:21 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	reset_sphere_state(t_object *object)
{
	object->u_data.sphere.center = object->u_data.sphere.initial_center;
	object->u_data.sphere.radius = object->u_data.sphere.initial_radius;
	update_object_matrix(object);
}
