/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:46:38 by eraad             #+#    #+#             */
/*   Updated: 2026/01/07 12:36:44 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

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
			display_progress(y, data->scene->mlx_window.height - 1);
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

static void	log_render_time(long	start_time)
{
	char	*temp_1;
	char	*temp_2;

	temp_1 = ft_itoa(get_time_ms() - start_time);
	temp_2 = ft_strjoin("Render time: ", temp_1);
	free(temp_1);
	temp_1 = ft_strjoin(temp_2, " ms");
	free(temp_2);
	log_event("PERF", temp_1, 0);
	free(temp_1);
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
	log_render_time(start_time);
}
