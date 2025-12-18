/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:37:48 by eraad             #+#    #+#             */
/*   Updated: 2025/12/18 16:42:25 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

//* ========================================================================= */
//*                                PROTOTYPES                                 */
//* ========================================================================= */
t_status	init_graphics(t_scene *scene);
t_status	render_frame(t_scene *scene);
void		image_pixel_put(t_image *img, int x, int y, int color);
int			color_to_int(t_color c);

#endif