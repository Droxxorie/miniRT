/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:38:32 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 22:50:08 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	resize_object(t_object *object, int key)
{
	t_real	k;

	if (!object)
		return ;
	if (key == KEY_PLUS)
		k = STEP_SIZE;
	else if (key == KEY_MINUS)
		k = -STEP_SIZE;
	else
		return ;
	if (object->type == SPHERE) //? peut etre faire une map ici aussi ?
	{
		object->data.sphere.radius += k;
		if (object->data.sphere.radius < 0.1)
			object->data.sphere.radius = 0.1;
		object->data.sphere.radius_squared = object->data.sphere.radius * object->data.sphere.radius;
	}
	else if (object->type == CYLINDER) //? rajouter touche pour hauteur ?
	{
		object->data.cylinder.radius += k;
		if (object->data.cylinder.radius < 0.1)
			object->data.cylinder.radius = 0.1;
		object->data.cylinder.radius_squared = object->data.cylinder.radius * object->data.cylinder.radius;
	}
}
