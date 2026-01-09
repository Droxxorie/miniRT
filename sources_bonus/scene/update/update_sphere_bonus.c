/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sphere_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:40:42 by eraad             #+#    #+#             */
/*   Updated: 2026/01/09 14:24:41 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	update_sphere(t_object *object)
{
	t_mat4		translation;
	t_mat4		scaling;
	t_mat4		transform;
	t_sphere	*sphere;

	sphere = &object->u_data.sphere;
	translation = make_translation_matrix(sphere->center);
	scaling = make_scale_matrix((t_vec3){sphere->radius, sphere->radius,
			sphere->radius});
	transform = identity_matrix();
	transform = mat4_mult_mat4(transform, translation);
	transform = mat4_mult_mat4(transform, scaling);
	sphere->sq_radius = sphere->radius * sphere->radius;
	if (sphere->radius > EPSILON)
		sphere->inv_radius = 1.0 / sphere->radius;
	else
		sphere->inv_radius = 0.0;
	set_transform(object, transform);
}
