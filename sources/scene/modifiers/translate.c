/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:47:18 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 12:15:17 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	translate_object(t_object *object, t_vec3 translation)
{
	if (object->type == SPHERE)
		object->u_data.sphere.center = vec3_add(object->u_data.sphere.center,
				translation);
	else if (object->type == PLANE)
		object->u_data.plane.origin = vec3_add(object->u_data.plane.origin,
				translation);
	else if (object->type == CYLINDER)
		object->u_data.cylinder.center = vec3_add(object->u_data.cylinder.center,
				translation);
	update_object_matrix(object);
}
