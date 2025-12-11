/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:48:17 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 22:54:57 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_color	get_ray_color(t_scene *scene, t_ray *ray)
{
	t_hit_record	record;

	if (hit_objects(scene->objects, ray, &record)) // TODO
		return (record.object->color);
	return ((t_color){0.0, 0.0, 0.0}); // ou ambient ?
	// return (scene->ambient);
}

void	render_scene(t_scene *scene, int x, int y, t_real u, t_real v)
{
	t_ray ray;
	t_color pixel_color;

	while (y < scene->mlx_window.height)
	{
		x = 0;
		while (x < scene->mlx_window.width)
		{
			u = (t_real)x / (t_real)(scene->mlx_window.width - 1);
			v = (t_real)(scene->mlx_window.height - 1 - y)
				/ (t_real)(scene->mlx_window.height - 1);
			get_ray(&scene->cameras[0], &ray, u, v); //? ne gere pas plusierus cams
			pixel_color = get_ray_color(scene, &ray); // TODO
			put_pixel_to_image(&scene->frame_buffer, x, y, pixel_color); //TODO pixel_color ou record->color ?
			x++;
		}
		print_progress(scene, y);
		y++;
	}
}
