/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_free_exit_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:52:17 by eraad             #+#    #+#             */
/*   Updated: 2026/01/05 16:08:15 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	sys_print_error_free_exit(t_scene *scene, const char *error_message)
{
	sys_print_error(error_message);
	clean_exit(scene, EXIT_FAILURE);
}

void	print_error_free_exit(t_scene *scene, const char *error_message)
{
	print_error(error_message);
	clean_exit(scene, EXIT_FAILURE);
}
