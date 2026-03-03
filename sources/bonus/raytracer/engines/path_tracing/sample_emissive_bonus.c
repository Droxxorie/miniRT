/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_emissive_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:46:32 by eraad             #+#    #+#             */
/*   Updated: 2026/03/03 16:47:54 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_vec3	sample_rect(t_object *obj, unsigned int *seed)
{
	t_vec3		tb[2];
	t_real		r[2];
	t_rectangle	*rect;

	rect = &obj->u_data.rectangle;
	build_onb(rect->normal, &tb[0], &tb[1]);
	r[0] = (random_double(seed) - 0.5) * rect->width;
	r[1] = (random_double(seed) - 0.5) * rect->height;
	return (vec3_add(rect->center,
			vec3_add(vec3_scale(tb[0], r[0]), vec3_scale(tb[1], r[1]))));
}

static t_vec3	sample_sphere(t_object *obj, unsigned int *seed)
{
	t_vec3	dir;

	dir = vec3_normalize(random_in_unit_sphere(seed));
	if (vec3_len_squared(dir) < EPSILON)
		dir = (t_vec3){1.0, 0.0, 0.0};
	return (vec3_add(obj->u_data.sphere.center,
			vec3_scale(dir, obj->u_data.sphere.radius)));
}

static t_vec3	sample_disk(t_object *obj, unsigned int *seed)
{
	t_vec3	tb[2];
	t_real	r;
	t_real	phi;

	build_onb(obj->u_data.disk.normal, &tb[0], &tb[1]);
	r = obj->u_data.disk.radius * sqrt(random_double(seed));
	phi = TWO_PI * random_double(seed);
	return (vec3_add(obj->u_data.disk.center,
			vec3_add(vec3_scale(tb[0], r * cos(phi)),
				vec3_scale(tb[1], r * sin(phi)))));
}

static t_vec3	sample_tri(t_object *obj, unsigned int *seed)
{
	t_real		r[2];
	t_real		u;
	t_real		v;
	t_triangle	*tri;

	tri = &obj->u_data.triangle;
	r[0] = sqrt(random_double(seed));
	r[1] = random_double(seed);
	u = 1.0 - r[0];
	v = r[0] * (1.0 - r[1]);
	return (vec3_add(vec3_add(vec3_scale(tri->p1, u),
				vec3_scale(tri->p2, v)),
			vec3_scale(tri->p3, r[0] * r[1])));
}

t_vec3	sample_emissive_point(t_object *obj, unsigned int *seed)
{
	if (obj->type == SPHERE)
		return (sample_sphere(obj, seed));
	if (obj->type == DISK)
		return (sample_disk(obj, seed));
	if (obj->type == TRIANGLE)
		return (sample_tri(obj, seed));
	return (sample_rect(obj, seed));
}
