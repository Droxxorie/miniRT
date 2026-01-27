/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:46:38 by eraad             #+#    #+#             */
/*   Updated: 2026/01/27 17:07:24 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	process_pixel(t_scene *s, int x, int y)
{
	t_ray			ray;
	t_color			final;
	t_color			accumulated;
	unsigned int	seeds[2];
	int				i;

	if ((int)s->samples_per_pixel == 1)
	{
		generate_ray(s->active_camera, &ray, (t_real)x, (t_real)y);
		final = cast_ray(s, &ray, MAX_REFLECTION_DEPTH);
		return (image_pixel_put(&s->frame_buffer, x, y, color_to_int(final)));
	}
	accumulated = (t_color){0.0, 0.0, 0.0};
	seeds[0] = generate_seed((t_point3){(t_real)x, (t_real)y, 0.0});
	i = -1;
	while (++i < (int)s->samples_per_pixel)
	{
		seeds[1] = pcg_hash(seeds[0] ^ i);
		generate_ray(s->active_camera, &ray, (t_real)x
			+ random_double(&seeds[1]) - 0.5, (t_real)y
			+ random_double(&seeds[1]) - 0.5);
		accumulated = color_add(accumulated, path_trace(s, ray, &seeds[1]));
	}
	final = color_div(accumulated, (t_real)i);
	image_pixel_put(&s->frame_buffer, x, y, color_to_int(final));
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

void	render_frame(t_scene *scene)
{
	pthread_t		*threads;
	t_thread_data	*data;
	int				thread_count;
	long			start_time;
	long			end_time;

	start_time = get_time_ms();
	thread_count = init_render_threads(scene, &threads, &data);
	start_render_threads(scene, thread_count, threads, data);
	wait_render_threads(thread_count, threads);
	cleanup_render_threads(scene, threads, data);
	if (scene->mlx_window.win_ptr)
		mlx_put_image_to_window(scene->mlx_window.mlx_ptr,
			scene->mlx_window.win_ptr, scene->frame_buffer.ptr, 0, 0);
	end_time = get_time_ms();
	log_event(stdout, "PERF", "Render time: %ld ms\r", end_time - start_time);
}
