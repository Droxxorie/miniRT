/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:39:41 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 12:16:02 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	translate_plane(t_object *object, t_vec3 translation)
{
	object->u_data.plane.origin = vec3_add(object->u_data.plane.origin, translation);
	update_object_matrix(object);
}
