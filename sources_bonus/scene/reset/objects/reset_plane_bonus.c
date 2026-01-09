/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_plane_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:55:15 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 08:55:00 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	reset_plane_state(t_object *object)
{
	object->u_data.plane.origin = object->u_data.plane.initial_origin;
	object->u_data.plane.normal = object->u_data.plane.initial_normal;
	update_object(object);
}
