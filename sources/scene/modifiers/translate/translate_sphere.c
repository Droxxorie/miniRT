/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:33:23 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 12:16:06 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	translate_sphere(t_object *object, t_vec3 translation)
{
	object->u_data.sphere.center = vec3_add(object->u_data.sphere.center, translation);
	update_object_matrix(object);
}
