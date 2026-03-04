/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:37:48 by eraad             #+#    #+#             */
/*   Updated: 2026/03/04 18:55:12 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_BONUS_H
# define GRAPHICS_BONUS_H

# include "structs/s_scene_bonus.h"
# include <pthread.h>

//* ========================================================================= */
//*                                PROTOTYPES                                 */
//* ========================================================================= */
int			color_to_int(t_color c);
void		process_pixel(t_scene *s, int x, int y);
void		*render_routine(void *arg);
void		render_frame(t_scene *scene);
t_status	init_graphics(t_scene *scene);
t_status	init_textures(t_scene *scene);
void		image_pixel_put(t_image *img, int x, int y, int color);
void		clear_buffer(t_image *buffer);
t_color		gamma_correction(t_color color);
t_color		aces_tone_mapping(t_color hdr);
void		draw_tile_border(t_scene *s, int x, int y);
void		build_spiral_order(t_scene *s);

//* --- Multi-threading --- */
void		wait_render_threads(int count, pthread_t *threads);
int			init_render_threads(t_scene *scene, pthread_t **threads,
				t_thread_data **data);
void		cleanup_render_threads(t_scene *scene, pthread_t *threads,
				t_thread_data *data);
void		start_render_threads(t_scene *scene, int count, pthread_t *threads,
				t_thread_data *data);

#endif