/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_bsdf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:17:04 by eraad             #+#    #+#             */
/*   Updated: 2026/01/26 20:58:06 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	init_prb_params(t_material *mat, t_hit_record *rec,
		t_cook_torrance_vars *v)
{
	v->albedo = get_albedo(mat, rec);
	v->roughness = mat->roughness;
	v->metallic = mat->metallic;
	if (mat->roughness_map)
		v->roughness = sample_texture(mat->roughness_map, rec->u, rec->v).r;
	if (mat->metallic_map)
		v->metallic = sample_texture(mat->metallic_map, rec->u, rec->v).r;
	v->f0 = (t_color){0.04, 0.04, 0.04};
	if (v->metallic > 0.5)
		v->f0 = mat->specular_color;
	else if (mat->roughness > 0.99)
		v->f0 = (t_color){0.0, 0.0, 0.0};
}

static t_color	calc_specular(t_cook_torrance_vars *v, t_color f)
{
	t_real	d;
	t_real	g;
	t_real	denom;

	d = distribution_ggx(v->n, v->h, v->roughness);
	g = geometry_smith(v->n, v->v, v->l, v->roughness);
	denom = 4.0 * v->n_dot_v * v->n_dot_l;
	return (color_div(color_scale(f, (d * g)), fmax(denom, 0.001)));
}

static t_color	apply_specular_fade(t_cook_torrance_vars *v, t_color specular)
{
	t_real	specular_fade;

	if (v->metallic < 0.1)
	{
		specular_fade = 1.0;
		if (v->roughness > 0.5)
			specular_fade = 1.0 - ((v->roughness - 0.5) * 2.0);
		specular = color_scale(specular, fmax(specular_fade, 0.0));
	}
	return (specular);
}

static t_color	compute_pbr_surface(t_material *mat, t_hit_record *rec,
		t_cook_torrance_vars *v)
{
	t_color	specular;
	t_color	diffuse;
	t_color	k_d;
	t_color	f;

	init_prb_params(mat, rec, v);
	f = fresnel_schlick(fmax(vec3_dot(v->h, v->v), 0.0), v->f0);
	specular = calc_specular(v, f);
	specular = apply_specular_fade(v, specular);
	k_d = color_scale(color_sub((t_color){1.0, 1.0, 1.0}, f), 1.0
			- v->metallic);
	diffuse = color_prod(k_d, color_scale(v->albedo, INV_PI));
	return (color_add(diffuse, specular));
}

t_color	eval_bsdf(t_material *mat, t_hit_record *rec, t_vec3 v, t_vec3 l)
{
	t_cook_torrance_vars	vars;

	if (mat->metallic < 0.01 && (mat->roughness >= 0.99 || mat->type == 0))
	{
		if (fmax(vec3_dot(rec->normal, l), 0.0) <= 0.0)
			return ((t_color){0.0, 0.0, 0.0});
		return (color_scale(get_albedo(mat, rec), INV_PI));
	}
	vars.v = v;
	vars.l = l;
	vars.n = rec->normal;
	vars.h = vec3_normalize(vec3_add(vars.v, vars.l));
	vars.n_dot_l = fmax(vec3_dot(vars.n, vars.l), 0.0);
	vars.n_dot_v = fmax(vec3_dot(vars.n, vars.v), 0.0);
	if (vars.n_dot_l <= EPSILON || vars.n_dot_v <= EPSILON)
		return ((t_color){0.0, 0.0, 0.0});
	return (compute_pbr_surface(mat, rec, &vars));
}
