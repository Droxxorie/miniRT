/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_rectangle_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 20:49:44 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 20:50:30 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	reset_rectangle_state(t_object *object)
{
	object->u_data.rectangle.center = object->u_data.rectangle.initial_center;
	object->u_data.rectangle.normal = object->u_data.rectangle.initial_normal;
	object->u_data.rectangle.width = object->u_data.rectangle.initial_width;
	object->u_data.rectangle.height = object->u_data.rectangle.initial_height;
	update_object_matrix(object);
}
