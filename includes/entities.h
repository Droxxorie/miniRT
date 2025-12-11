/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:29:56 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 15:09:13 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# include <color.h>

typedef struct s_light
{
	t_point3		position; //origin
	t_real			brightness; //intensity
	t_color			color;
	t_vec3			direction;
	t_real			distance;
	t_real			angle;
	struct s_light	*next;
}	t_light;

typedef struct s_camera
{
	int				id;
	t_point3		position; //origin
	t_vec3			direction; //normal
	int				fov;
	t_real			viewport_width;
	t_real			viewport_height;
	t_vec3			horizontal;
	t_vec3			vertical;
	t_vec3			lower_left_corner;
	struct s_camera	*next;
}	t_camera;

void	setup_camera(t_camera *c, t_real aspect_ratio);
void	prepare_cameras(t_scene *scene);
void	get_ray(t_camera *camera, t_ray *ray, t_real u, t_real v);

#endif