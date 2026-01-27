/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_skybox_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 22:14:29 by eraad             #+#    #+#             */
/*   Updated: 2026/01/27 15:18:19 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static t_color	get_sunset_gradient(t_scene *scene, t_real y)
{
	t_color	horizon;
	t_color	zenith;
	t_color	ground;
	t_real	t;

	(void)scene;
	horizon = (t_color){1.0, 0.6, 0.4};
	zenith = (t_color){0.2, 0.2, 0.45};
	ground = (t_color){0.15, 0.15, 0.15};
	if (y < 0.0)
	{
		t = -y * 2.0;
		if (t > 1.0)
			t = 1.0;
		return (color_mix(horizon, ground, t));
	}
	t = pow(y, 0.6);
	return (color_mix(horizon, zenith, t));
}

static t_color	apply_clouds(t_vec3 dir, t_color bg_color)
{
	t_real	noise;
	t_real	density;
	t_color	white;
	t_real	scale;

	if (dir.y < 0.1)
		return (bg_color);
	scale = 2.0;
	noise = noise_2d(dir.x * scale, dir.z * scale);
	noise = (noise + 1.0) * 0.5;
	if (noise < 0.45)
		return (bg_color);
	density = (noise - 0.45) * 2.0;
	if (density > 1.0)
		density = 1.0;
	density *= ft_clamp((dir.y - 0.1) * 2.0, 0.0, 1.0);
	white = (t_color){0.95, 0.95, 0.95};
	return (color_mix(bg_color, white, density));
}

static t_color	procedural_sky(t_scene *scene, t_ray *ray)
{
	t_vec3	dir;
	t_color	bg_color;

	dir = vec3_normalize(ray->direction);
	bg_color = get_sunset_gradient(scene, dir.y);
	return (apply_clouds(dir, bg_color));
}

t_color	get_skybox_color(t_scene *scene, t_ray *ray)
{
	t_vec3	dir;
	t_real	u;
	t_real	v;

	if (!scene->skybox_map)
		return (procedural_sky(scene, ray));
	dir = vec3_normalize(ray->direction);
	u = 0.5 - (atan2(dir.z, dir.x) * INV_TWO_PI);
	v = 0.5 + (asin(dir.y) * INV_PI);
	return (sample_texture(scene->skybox_map, u, v));
}
