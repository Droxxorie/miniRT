/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:29:56 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 08:27:38 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# define MAX_LIGHTS 1
# define MAX_CAMERAS 16

typedef struct s_color
{
	t_real			r;
	t_real			g;
	t_real			b;
}					t_color;

typedef struct s_light
{
	t_point3		position; // origin
	t_real			brightness; // intensity
	t_color			color;
	struct s_light	*next;
}					t_light;

typedef struct s_camera
{
	int				id;
	t_point3		position; // origin
	t_vec3			direction;  // normal
	int				fov;
	t_real			viewport_width;
	t_real			viewport_height;
	t_vec3			horizontal;
	t_vec3			vertical;
	t_vec3			lower_left_corner;
	struct s_camera	*next;
}					t_camera;

void	setup_camera(t_camera *c, t_real aspect_ratio);
void	prepare_cameras(t_scene *scene);

#endif