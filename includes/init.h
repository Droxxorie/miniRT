/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:37:17 by eraad             #+#    #+#             */
/*   Updated: 2025/12/11 17:34:33 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <utils.h>
# include <engine.h>
# include <objects.h>

t_status	load_scene(t_scene *scene, char *file_path);
t_status	init_graphics(t_scene *scene);

#endif