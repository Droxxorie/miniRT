/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:37:28 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 09:12:21 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	update_object(t_object *object)
{
	if (object->type == SPHERE)
		update_sphere(object);
	else if (object->type == PLANE)
		update_plane(object);
	else if (object->type == CYLINDER)
		update_cylinder(object);
	else if (object->type == RECTANGLE)
		update_rectangle(object);
	else if (object->type == DISK)
		update_disk(object);
	else if (object->type == TRIANGLE)
		update_triangle(object);
}
