/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:13:06 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 17:33:06 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	setup_camera(t_camera *c, t_real aspect_ratio)
{
	t_real	theta;
	t_vec3 w; //* forward
	t_vec3 u; //* right
	t_vec3 v; //* up

	if (c == NULL)
		return ;
	theta = c->fov * (PI / 180.0);
	c->viewport_height = 2.0 * tan(theta * 0.5);
	c->viewport_width = aspect_ratio * c->viewport_height;
	w = vec3_normalize(c->direction);
	if (fabs(w.y > 0.99999))
		u = vec3_normalize(vec3_cross((t_vec3){0, 0, 1}, w)); //* world_up devient z
	else
		u = vec3_normalize(vec3_cross((t_vec3){0, 1, 0}, w)); //* world_up devient y (standard)
	v = vec3_cross(w, u);
	c->horizontal = vec3_scale(u, c->viewport_width);
	c->vertical = vec3_scale(v, c->viewport_height);
	c->lower_left_corner = c->position;
	c->lower_left_corner = vec3_sub(c->lower_left_corner,
			vec3_scale(c->horizontal, 0.5));
	c->lower_left_corner = vec3_sub(c->lower_left_corner,
			vec3_scale(c->vertical, 0.5));
	c->lower_left_corner = vec3_add(c->lower_left_corner, w);
}

void	prepare_cameras(t_scene *scene)
{
	t_camera	*current;

	if (scene == NULL || scene->cameras == NULL)
		return ;
	current = scene->cameras;
	while (current)
	{
		setup_camera(current, scene->mlx_window.aspect_ratio);
		current = current->next;
	}
	scene->active_camera = scene->cameras;
}
