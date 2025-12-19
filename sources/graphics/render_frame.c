/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:46:38 by eraad             #+#    #+#             */
/*   Updated: 2025/12/19 10:43:52 by eraad            ###   ########.fr       */
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
		ft_putstr_fd("\r\033[2KRendering: ", 1);
		ft_putnbr_fd(percent, 1);
		ft_putstr_fd("%", 1);
	}
	if (y >= scene->mlx_window.height - 1)
		ft_putstr_fd("\r\033[2K", STDOUT_FILENO);
}

static void	process_pixel(t_scene *scene, int x, int y)
{
	t_ray	ray;
	t_color	color;

	generate_ray(scene->active_camera, &ray, (t_real)x, (t_real)y);
	color = compute_pixel_color(scene, &ray);
	image_pixel_put(&scene->frame_buffer, x, y, color_to_int(color));
}

static void	render_scene(t_scene *scene)
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
		print_progress(scene, y);
		y++;
	}
	print_progress(scene, scene->mlx_window.height);
}

t_status	render_frame(t_scene *scene)
{
	render_scene(scene);
	if (scene->mlx_window.win_ptr)
		mlx_put_image_to_window(scene->mlx_window.mlx_ptr,
			scene->mlx_window.win_ptr, scene->frame_buffer.ptr, 0, 0);
	return (EXIT_SUCCESS);
}
