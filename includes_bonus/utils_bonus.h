/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:38:34 by eraad             #+#    #+#             */
/*   Updated: 2026/01/05 19:18:22 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "macros_bonus.h"
# include "structures_bonus.h"

//* ========================================================================= */
//*                                PRINT & LOG                                */
//* ========================================================================= */
void		print_usage(void);
void		log_info(const char *msg);
void		log_scene_stats(t_scene *scene);
void		print_object_details(t_object_type type);
void		log_detail(const char *message, const char *detail);

//* ========================================================================= */
//*                                STRINGS                                    */
//* ========================================================================= */
size_t		ft_strspn(const char *str, const char *accept);
size_t		ft_strcspn(const char *str, const char *reject);

//* ========================================================================= */
//*                                CORE/CLEANUP                               */
//* ========================================================================= */
void		destroy_scene(t_scene *scene);
t_status	clean_exit(t_scene *scene, t_status status);

//* ========================================================================= */
//*                                TIME                                       */
//* ========================================================================= */
long		get_time_ms(void);

#endif