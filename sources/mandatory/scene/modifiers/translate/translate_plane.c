/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:39:41 by eraad             #+#    #+#             */
/*   Updated: 2025/12/20 19:10:21 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	translate_plane(t_object *object, t_vec3 translation)
{
	t_plane	*plane;

	if (!object)
		return ;
	plane = &object->u_data.plane;
	plane->origin = vec3_add(plane->origin, translation);
	update_object_matrix(object);
}
