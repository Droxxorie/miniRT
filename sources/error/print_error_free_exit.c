/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_free_exit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:52:17 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 19:34:33 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

//* PAS ENCORE UTILISEE
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
