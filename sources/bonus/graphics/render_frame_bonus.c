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
	int	idx;

	pthread_mutex_lock(&s->tile_mutex);
	idx = s->next_tile;
	s->next_tile++;
	pthread_mutex_unlock(&s->tile_mutex);
	return (idx);
}

void	*render_routine(void *arg)
{
	t_thread_data	*data;
	int				seq;
	int				tile;
	int				eff;

	data = (t_thread_data *)arg;
	eff = TILE_SIZE * (int)fmax(data->scene->render_scale, 1.0);
	while (1)
	{
		seq = grab_next_tile(data->scene);
		if (seq >= data->scene->total_tiles)
			break ;
		tile = data->scene->tile_order[seq];
		draw_tile_border(data->scene,
			(tile % data->scene->tiles_per_row) * eff,
			(tile / data->scene->tiles_per_row) * eff);
		render_tile(data->scene,
			(tile % data->scene->tiles_per_row) * eff,
			(tile / data->scene->tiles_per_row) * eff);
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
	while (scene->next_tile < scene->total_tiles)
	{
		usleep(DISPLAY_INTERVAL_US);
		display_progress(scene->next_tile, scene->total_tiles);
		if (scene->mlx_window.win_ptr)
			mlx_put_image_to_window(scene->mlx_window.mlx_ptr,
				scene->mlx_window.win_ptr, scene->frame_buffer.ptr, 0, 0);
	}
	wait_render_threads(thread_count, threads);
	display_progress(scene->total_tiles, scene->total_tiles);
	cleanup_render_threads(scene, threads, data);
	if (scene->mlx_window.win_ptr)
		mlx_put_image_to_window(scene->mlx_window.mlx_ptr,
			scene->mlx_window.win_ptr, scene->frame_buffer.ptr, 0, 0);
	end_time = get_time_ms();
	log_event(stdout, "PERF", "Render time: %ld ms\n", end_time - start_time);
}
