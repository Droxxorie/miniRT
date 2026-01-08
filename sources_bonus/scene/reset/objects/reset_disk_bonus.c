/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_disk_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:44:55 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 21:45:29 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	reset_disk_state(t_object *object)
{
	object->u_data.disk.center = object->u_data.disk.initial_center;
	object->u_data.disk.normal = object->u_data.disk.initial_normal;
	object->u_data.disk.radius = object->u_data.disk.initial_radius;
	update_object_matrix(object);
}
