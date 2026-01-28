/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_julia_set_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 21:39:31 by eraad             #+#    #+#             */
/*   Updated: 2026/01/28 14:03:11 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_color	get_base_palette(t_real n)
{
	t_color	color;
	t_real	t;

	t = log2(n) * 0.9 + 3.5;
	color.r = 0.5 + 0.5 * cos(t + 0.0);
	color.g = 0.5 + 0.5 * cos(t + 0.6);
	color.b = 0.5 + 0.5 * cos(t + 1.0);
	return (color);
}

static t_julia_vars	julia_set_iters(t_vec4 z0, t_vec4 c, int max_steps,
		t_bool derivate)
{
	t_julia_vars	vars;
	int				i;

	vars.z = z0;
	vars.magnitude_sq = 0.0;
	vars.dz = 1.0;
	vars.trap_d = 1e10;
	vars.n = 0.0;
	i = -1;
	while (++i < max_steps)
	{
		if (derivate)
			vars.dz *= 9.0 * vec4_len_squared(q_square(vars.z));
		vars.z = vec4_add(q_cube(vars.z), c);
		vars.magnitude_sq = vec4_len_squared(vars.z);
		vars.trap_d = fmin(vars.trap_d, vec2_len(vec2_sub((t_vec2){vars.z.x,
						vars.z.z}, (t_vec2){0.45, 0.55})) - 0.1);
		if (vars.magnitude_sq > 256.0)
			break ;
		vars.n += 1.0;
	}
	return (vars);
}

t_color	get_julia_set_color(t_point3 p, t_object *object)
{
	t_julia_vars	vars;
	t_color			col;
	t_vec4			z0;
	t_vec4			c;
	t_julia_set		*set;

	set = &object->u_data.julia_set;
	c = set->c_constant;
	if (set->preset == TRUE)
		c = (t_vec4){-0.090909, 0.272727, 0.681818, -0.272727};
	z0 = (t_vec4){p.x, p.y, p.z, 0.0};
	vars = julia_set_iters(z0, c, 300, FALSE);
	col = get_base_palette(vars.n);
	if (p.y > 0.0)
		col = color_mix(col, (t_color){1.0, 1.0, 1.0}, 0.2);
	return (apply_shading(col, vars.n));
}

t_real	sdf_julia_set(t_point3 p, t_object *object)
{
	t_julia_vars	vars;
	t_real			dist;
	t_vec4			z0;
	t_vec4			c;
	t_julia_set		*set;

	set = &object->u_data.julia_set;
	c = set->c_constant;
	if (set->preset == TRUE)
		c = (t_vec4){-0.090909, 0.272727, 0.681818, -0.272727};
	z0 = (t_vec4){p.x, p.y, p.z, 0.0};
	vars = julia_set_iters(z0, c, 200, TRUE);
	dist = 0.25 * log(vars.magnitude_sq) * sqrt(vars.magnitude_sq / vars.dz);
	if (set->orbital_trap)
		dist = fmin(dist, vars.trap_d);
	if (set->cut)
		dist = fmax(dist, p.y - 0.1);
	return (fmin(dist, 4.0));
}
