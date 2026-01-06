/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:46:38 by eraad             #+#    #+#             */
/*   Updated: 2026/01/06 17:04:04 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	print_progress(t_scene *scene, int y)
{
	int	percent;

	percent = (y * 100) / scene->mlx_window.height;
	if (percent != ((y - 1) * 100) / scene->mlx_window.height)
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

void	*render_routine(void *arg)
{
	t_thread_data	*data;
	int				x;
	int				y;

	data = (t_thread_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->scene->line_mutex);
		y = data->scene->next_line;
		data->scene->next_line++;
		if (y < data->scene->mlx_window.height)
			print_progress(data->scene, y);
		pthread_mutex_unlock(&data->scene->line_mutex);
		if (y >= data->scene->mlx_window.height)
			break ;
		x = 0;
		while (x < data->scene->mlx_window.width)
		{
			process_pixel(data->scene, x, y);
			x++;
		}
	}
	return (NULL);
}

void	render_frame(t_scene *scene)
{
	pthread_t		*threads;
	t_thread_data	*data;
	int				thread_count;
	long			start_time;

	start_time = get_time_ms();
	thread_count = init_render_threads(scene, &threads, &data);
	start_render_threads(scene, thread_count, threads, data);
	wait_render_threads(thread_count, threads);
	cleanup_render_threads(scene, threads, data);
	if (scene->mlx_window.win_ptr)
		mlx_put_image_to_window(scene->mlx_window.mlx_ptr,
			scene->mlx_window.win_ptr, scene->frame_buffer.ptr, 0, 0);
	ft_putstr_fd("Render time: ", STDOUT_FILENO);
	ft_putnbr_fd(get_time_ms() - start_time, STDOUT_FILENO);
	ft_putstr_fd(" ms\n", STDOUT_FILENO);
}
