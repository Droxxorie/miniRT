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

static t_color	compute_whitted(t_scene *scene, int x, int y,
		unsigned int *seed)
{
	t_color	accumulated;
	t_ray	ray;
	t_real	u;
	t_real	v;
	int		i;

	accumulated = (t_color){0.0, 0.0, 0.0};
	i = 0;
	while (i < (int)scene->aa_samples)
	{
		u = (t_real)x;
		v = (t_real)y;
		if (scene->aa_samples > 1)
		{
			seed[1] = pcg_hash(seed[0] ^ i);
			u += random_double(&seed[1]) - 0.5;
			v += random_double(&seed[1]) - 0.5;
		}
		generate_ray(scene->active_camera, &ray, u, v);
		accumulated = color_add(accumulated, cast_ray(scene, &ray,
					MAX_REFLECTION_DEPTH));
		i++;
	}
	return (color_div(accumulated, (t_real)i));
}

static t_color	compute_pathtrace(t_scene *scene, int x, int y,
		unsigned int *seed)
{
	t_color	accumulated;
	t_ray	ray;
	int		i;

	accumulated = (t_color){0.0, 0.0, 0.0};
	i = 0;
	while (i < (int)scene->samples_per_pixel)
	{
		seed[1] = pcg_hash(seed[0] ^ i);
		generate_ray(scene->active_camera, &ray, (t_real)x
			+ random_double(&seed[1]) - 0.5, (t_real)y + random_double(&seed[1])
			- 0.5);
		accumulated = color_add(accumulated, path_trace(scene, ray, &seed[1]));
		i++;
	}
	return (color_div(accumulated, (t_real)i));
}

static void	process_pixel(t_scene *s, int x, int y)
{
	t_color			final;
	unsigned int	seeds[2];
	int				i;
	int				j;
	int				color;

	seeds[0] = generate_seed((t_point3){(t_real)x, (t_real)y, 0.0});
	if (s->render_scale > 1.0)
		final = compute_whitted(s, x, y, seeds);
	else if ((int)s->samples_per_pixel == 1)
		final = compute_whitted(s, x, y, seeds);
	else
		final = compute_pathtrace(s, x, y, seeds);
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
