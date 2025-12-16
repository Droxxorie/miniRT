/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_free_exit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:52:17 by eraad             #+#    #+#             */
/*   Updated: 2025/12/16 22:59:03 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	sys_print_error_free_exit(t_scene *scene, const char *error_message)
{
	ft_putstr_fd(B_RED "Error\n" RESET, STDERR_FILENO);
	if (error_message)
	{
		// ft_putstr_fd(error_message, STDERR_FILENO);
		// ft_putstr_fd(": ", STDERR_FILENO);
		ft_printf_fd(STDERR_FILENO, "%s: ", error_message);
	}
	// ft_putstr_fd(strerror(errno), STDERR_FILENO);
	// ft_putstr_fd("\n", STDERR_FILENO);
	ft_printf_fd(STDERR_FILENO, "%s\n", strerror(errno));
	clean_exit(scene, EXIT_FAILURE);
}

void	print_error_free_exit(t_scene *scene, const char *error_message)
{
	ft_putstr_fd(B_RED "Error\n" RESET, STDERR_FILENO);
	if (error_message)
	{
		// ft_putstr_fd(error_message, STDERR_FILENO);
		// ft_putstr_fd("\n", STDERR_FILENO);
		ft_printf_fd(STDERR_FILENO, "%s\n", error_message);
	}
	clean_exit(scene, EXIT_FAILURE);
}
