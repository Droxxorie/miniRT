/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:38:34 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 21:57:46 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "macros.h"
# include "structures.h"

void		print_usage(void);
void		print_object_details(t_object_type type);
void		log_info(const char *msg);
void		log_detail(const char *message, const char *detail);
void		log_scene_stats(t_scene *scene);

size_t		ft_strcspn(const char *str, const char *reject);
size_t		ft_strspn(const char *str, const char *accept);

void		destroy_scene(t_scene *scene);
t_status	clean_exit(t_scene *scene, t_status status);

#endif