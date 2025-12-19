/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:41:02 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 12:15:57 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	translate_cylinder(t_object *object, t_vec3 translation)
{
	object->u_data.cylinder.center = vec3_add(
			object->u_data.cylinder.center, translation);
	update_object_matrix(object);
}
