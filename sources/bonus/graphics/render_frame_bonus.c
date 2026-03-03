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

static t_color	sample_pixel_once(t_scene *scene, int *xyi,
		unsigned int *seed)
{
	t_ray		ray;
	t_point3	uv;
	t_bool		use_whitted;
	t_bool		do_jitter;

	seed[1] = pcg_hash(seed[0] ^ ((unsigned int)xyi[2] * 2654435769u));
	uv.x = (t_real)xyi[0];
	uv.y = (t_real)xyi[1];
	use_whitted = (scene->render_scale > 1.0
			|| (int)scene->samples_per_pixel == 1);
	do_jitter = (scene->render_scale > 1.0
			|| (int)scene->samples_per_pixel == 1);
	if (do_jitter && (int)scene->aa_samples <= 1)
		do_jitter = FALSE;
	if (!do_jitter && (int)scene->samples_per_pixel > 1)
		do_jitter = TRUE;
	if (do_jitter)
	{
		uv.x += random_double(&seed[1]) - 0.5;
		uv.y += random_double(&seed[1]) - 0.5;
	}
	generate_ray(scene->active_camera, &ray, uv.x, uv.y);
	if (use_whitted == TRUE)
		return (cast_ray(scene, &ray, MAX_REFLECTION_DEPTH));
	return (path_trace(scene, ray, &seed[1]));
}

static t_color	compute_pixel_color(t_scene *scene, int x, int y,
		unsigned int *seed)
{
	t_color	accumulated;
	int		xyi[3];
	int		i;
	int		n;

	if (scene->render_scale > 1.0 || (int)scene->samples_per_pixel == 1)
		n = (int)scene->aa_samples;
	else
		n = (int)scene->samples_per_pixel;
	accumulated = (t_color){0.0, 0.0, 0.0};
	xyi[0] = x;
	xyi[1] = y;
	i = 0;
	while (i < n)
	{
		xyi[2] = i;
		accumulated = color_add(accumulated, sample_pixel_once(scene, xyi,
					seed));
		i++;
	}
	return (color_div(accumulated, (t_real)n));
}

static void	process_pixel(t_scene *s, int x, int y)
{
	t_color			final;
	unsigned int	seeds[2];
	int				color;
	int				i;
	int				j;

	seeds[0] = pcg_hash((unsigned int)x * 2654435761u
			^ (unsigned int)y * 805459861u);
	final = compute_pixel_color(s, x, y, seeds);
	final = aces_tone_mapping(final);
	final = gamma_correction(final);
	color = color_to_int(final);
	i = -1;
	while (++i < (int)s->render_scale)
	{
		j = -1;
		while (++j < (int)s->render_scale)
		{
			if (x + i < s->mlx_window.width && y + j < s->mlx_window.height)
				image_pixel_put(&s->frame_buffer, x + i, y + j, color);
		}
	}
}

void	*render_routine(void *arg)
{
	t_thread_data	*data;
	int				x;
	int				y;
	int				scale;

	data = (t_thread_data *)arg;
	scale = (int)(data->scene->render_scale);
	while (1)
	{
		pthread_mutex_lock(&data->scene->line_mutex);
		y = data->scene->next_line;
		data->scene->next_line += scale;
		if (y < data->scene->mlx_window.height)
			display_progress(y, data->scene->mlx_window.height - 1);
		pthread_mutex_unlock(&data->scene->line_mutex);
		if (y >= data->scene->mlx_window.height)
			break ;
		x = 0;
		while (x < data->scene->mlx_window.width)
		{
			process_pixel(data->scene, x, y);
			x += scale;
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
