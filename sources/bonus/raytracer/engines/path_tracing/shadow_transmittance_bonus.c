/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_transmittance_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:47:55 by eraad             #+#    #+#             */
/*   Updated: 2026/03/03 18:16:45 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_bool	can_pass_through(t_material *mat)
{
	if (mat->type == DIELECTRIC || mat->transparency > 0.001)
		return (TRUE);
	if (mat->emission_color.r > EPSILON || mat->emission_color.g > EPSILON
		|| mat->emission_color.b > EPSILON)
		return (TRUE);
	return (FALSE);
}

static void	absorb_through(t_material *mat, t_real dist, t_color *trans)
{
	if (mat->type == DIELECTRIC)
	{
		*trans = beer_lambert(*trans, dist, mat->absorbance);
		return ;
	}
	if (mat->transparency > 0.001)
		*trans = color_scale(*trans, mat->transparency);
}

static void	init_shadow_ray(t_hit_record *rec, t_light_sample_vars *v,
		t_ray *ray)
{
	ray->origin = vec3_add(rec->hit_point,
			vec3_scale(rec->normal, 0.1));
	ray->direction = v->light_dir;
	ray->min = 0.01;
	ray->is_shadow_ray = TRUE;
	ray->max = v->dist - 0.1;
}

static int	trace_through_layer(t_ray *ray, t_bvh_node *root,
		t_color *trans)
{
	t_hit_record	shadow_rec;
	t_material		*mat;

	if (!hit_bvh(root, ray, &shadow_rec))
		return (0);
	mat = shadow_rec.object->material;
	if (!mat || !can_pass_through(mat))
		return (2);
	absorb_through(mat, shadow_rec.t, trans);
	ray->origin = ray_at(ray, shadow_rec.t + 0.01);
	ray->max -= (shadow_rec.t + 0.01);
	return (1);
}

t_bool	is_occulted(t_path_info *i, t_hit_record *rec,
		t_light_sample_vars *v)
{
	t_ray	ray;
	int		layer;
	int		status;

	v->transmittance = (t_color){1.0, 1.0, 1.0};
	init_shadow_ray(rec, v, &ray);
	layer = -1;
	status = 0;
	while (++layer < 12)
	{
		status = trace_through_layer(&ray, i->bvh_root, &v->transmittance);
		if (status != 1)
			break ;
	}
	if (status == 2 || color_mean(v->transmittance) < EPSILON)
		return (TRUE);
	return (FALSE);
}
