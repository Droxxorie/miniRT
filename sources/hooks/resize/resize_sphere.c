/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:18:57 by eraad             #+#    #+#             */
/*   Updated: 2025/12/15 13:19:50 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	resize_sphere(t_object *object, int key)
{
	t_real	k;

	if (key == KEY_PLUS)
		k = STEP_SIZE;
	else
		k = -STEP_SIZE;
	object->data.sphere.radius += k;
	if (object->data.sphere.radius < 0.1)
		object->data.sphere.radius = 0.1;
	object->data.sphere.radius_squared = object->data.sphere.radius
		* object->data.sphere.radius;
}
