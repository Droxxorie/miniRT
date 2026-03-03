/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:46:38 by eraad             #+#    #+#             */
/*   Updated: 2026/01/28 17:16:40 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	render_tile(t_scene *s, int tile_x, int tile_y)
{
	int	x;
	int	y;
	int	scale;
	int	lim[2];

	scale = (int)s->render_scale;
	if (scale < 1)
		scale = 1;
	lim[0] = tile_x + TILE_SIZE * scale;
	lim[1] = tile_y + TILE_SIZE * scale;
	if (lim[0] > s->mlx_window.width)
		lim[0] = s->mlx_window.width;
	if (lim[1] > s->mlx_window.height)
		lim[1] = s->mlx_window.height;
	y = tile_y;
	while (y < lim[1])
	{
		x = tile_x;
		while (x < lim[0])
		{
			process_pixel(s, x, y);
			x += scale;
		}
		y += scale;
	}
}

static int	grab_next_tile(t_scene *s)
{
	int	tile_idx;

	pthread_mutex_lock(&s->tile_mutex);
	tile_idx = s->next_tile;
	s->next_tile++;
	if (tile_idx < s->total_tiles)
		display_progress(tile_idx, s->total_tiles);
	pthread_mutex_unlock(&s->tile_mutex);
	return (tile_idx);
}

void	*render_routine(void *arg)
{
	t_thread_data	*data;
	int				tile_idx;
	int				scale;

	data = (t_thread_data *)arg;
	scale = (int)data->scene->render_scale;
	if (scale < 1)
		scale = 1;
	while (1)
	{
		tile_idx = grab_next_tile(data->scene);
		if (tile_idx >= data->scene->total_tiles)
			break ;
		render_tile(data->scene,
			(tile_idx % data->scene->tiles_per_row) * TILE_SIZE * scale,
			(tile_idx / data->scene->tiles_per_row) * TILE_SIZE * scale);
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
