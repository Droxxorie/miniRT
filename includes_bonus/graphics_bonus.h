/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:37:48 by eraad             #+#    #+#             */
/*   Updated: 2026/01/06 17:03:14 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_BONUS_H
# define GRAPHICS_BONUS_H

//* ========================================================================= */
//*                                PROTOTYPES                                 */
//* ========================================================================= */
int			color_to_int(t_color c);
void		render_frame(t_scene *scene);
void		*render_routine(void *arg);
t_status	init_graphics(t_scene *scene);
void		image_pixel_put(t_image *img, int x, int y, int color);

//* --- Multi-threading --- */
int			init_render_threads(t_scene *scene,
				pthread_t **threads, t_thread_data **data);
void		start_render_threads(t_scene *scene, int count,
				pthread_t *threads, t_thread_data *data);
void		wait_render_threads(int count, pthread_t *threads);
void		cleanup_render_threads(t_scene *scene, pthread_t *threads,
				t_thread_data *data);

#endif