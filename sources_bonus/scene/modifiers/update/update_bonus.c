/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:37:28 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 17:45:05 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	update_object_matrix(t_object *object)
{
	if (object->type == SPHERE)
		update_sphere_matrix(object);
	else if (object->type == PLANE)
		update_plane_matrix(object);
	else if (object->type == CYLINDER)
		update_cylinder_matrix(object);
	else if (object->type == RECTANGLE)
		update_rectangle_matrix(object);
}
