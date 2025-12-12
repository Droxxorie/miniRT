/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 22:54:09 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 22:55:43 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	translate_object(t_object *object, t_vec3 translation)
{
	if (!object)
		return ;
	if (object->type == SPHERE)
		object->data.sphere.center = vec3_add(object->data.sphere.center, translation);
	else if (object->type == PLANE)
		object->data.plane.origin = vec3_add(object->data.plane.origin, translation);
	else if (object->type == CYLINDER)
		object->data.cylinder.center = vec3_add(object->data.cylinder.center, translation);
	else
		return ;
}
