/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:56:27 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 11:58:30 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	resize_object_radius(t_object *object, t_real scale_amount)
{
	if (object->type == SPHERE)
	{
		object->u_data.sphere.radius += scale_amount;
		if (object->u_data.sphere.radius < 0.1)
			object->u_data.sphere.radius = 0.1;
	}
	else if (object->type == CYLINDER)
	{
		object->u_data.cylinder.radius += scale_amount;
		if (object->u_data.cylinder.radius < 0.1)
			object->u_data.cylinder.radius = 0.1;
	}
	update_object_matrix(object);
}

void	resize_object_height(t_object *object, t_real scale_amount)
{
	if (object->type == CYLINDER)
	{
		object->u_data.cylinder.height += scale_amount;
		if (object->u_data.cylinder.height < 0.1)
			object->u_data.cylinder.height = 0.1;
	}
	update_object_matrix(object);
}
