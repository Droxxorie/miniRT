/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:52:46 by eraad             #+#    #+#             */
/*   Updated: 2026/01/29 10:31:38 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

static void	compute_tile_grid(t_scene *scene)
{
	int	w;
	int	h;
	int	scale;

	scale = (int)scene->render_scale;
	if (scale < 1)
		scale = 1;
	w = (scene->mlx_window.width + TILE_SIZE * scale - 1)
		/ (TILE_SIZE * scale);
	h = (scene->mlx_window.height + TILE_SIZE * scale - 1)
		/ (TILE_SIZE * scale);
	scene->tiles_per_row = w;
	scene->total_tiles = w * h;
	scene->next_tile = 0;
}

int	init_render_threads(t_scene *scene, pthread_t **threads,
		t_thread_data **data)
{
	int	thread_count;

	thread_count = sysconf(_SC_NPROCESSORS_ONLN);
	if (thread_count <= 0 || thread_count > 24)
		thread_count = 4;
	*threads = malloc(sizeof(pthread_t) * thread_count);
	*data = malloc(sizeof(t_thread_data) * thread_count);
	if (!*threads || !*data)
		sys_print_error_free_exit(scene, ERR_MEM);
	compute_tile_grid(scene);
	if (pthread_mutex_init(&scene->tile_mutex, NULL) != 0)
		sys_print_error_free_exit(scene, ERR_MUTEX);
	return (thread_count);
}

void	start_render_threads(t_scene *scene, int count, pthread_t *threads,
		t_thread_data *data)
{
	int	i;

	i = 0;
	while (i < count)
	{
		data[i].thread_id = i;
		data[i].scene = scene;
		if (pthread_create(&threads[i], NULL, (void *)render_routine,
				&data[i]) != 0)
			sys_print_error_free_exit(scene, ERR_THREAD);
		i++;
	}
}

void	wait_render_threads(int count, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	cleanup_render_threads(t_scene *scene, pthread_t *threads,
		t_thread_data *data)
{
	pthread_mutex_destroy(&scene->tile_mutex);
	free(threads);
	free(data);
}
