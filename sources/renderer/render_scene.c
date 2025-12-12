/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:48:17 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 17:36:35 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static void	print_progress(t_scene *scene, int y)
{
	int	percent;
	int	prev_percent;

	percent = (y * 100) / scene->mlx_window.height;
	prev_percent = ((y - 1) * 100) / scene->mlx_window.height;
	if (percent != prev_percent || y == 0)
	{
		ft_putstr_fd("\rRendering... ", 1);
		ft_putnbr_fd(percent, 1);
		ft_putstr_fd("%", 1);
		if (percent == 100)
			ft_putstr_fd("\n", 1);
	}
}

static void	process_pixel(t_scene *scene, int x, int y)
{
	t_real	u;
	t_real	v;
	t_ray	ray;
	t_color	color;

	u = (t_real)x / (t_real)(scene->mlx_window.width - 1);
	v = (t_real)(scene->mlx_window.height - 1 - y)
		/ (t_real)(scene->mlx_window.height - 1);
	get_ray(scene->active_camera, &ray, u, v);
	color = get_ray_color(scene, &ray);
	image_pixel_put(&scene->frame_buffer, x, y, color_to_int(color));
}

void	render_scene(t_scene *scene)
{
	int	x;
	int	y;

	y = 0;
	while (y < scene->mlx_window.height)
	{
		x = 0;
		while (x < scene->mlx_window.width)
		{
			process_pixel(scene, x, y);
			x++;
		}
		print_progress(scene, y); //* Debug progress bar
		y++;
	}
	print_progress(scene, scene->mlx_window.height); //* Debug progress bar
}
