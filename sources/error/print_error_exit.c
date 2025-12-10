/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:24:58 by eraad             #+#    #+#             */
/*   Updated: 2025/12/10 17:36:41 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	sys_print_error_exit(const char *error_message)
{
	ft_putstr_fd(B_RED "Error: " RESET, STDERR_FILENO);
	if (error_message)
	{
		// ft_putstr_fd(error_message, STDERR_FILENO);
		// ft_putstr_fd(": ", STDERR_FILENO);
		ft_printf_fd(STDERR_FILENO, "%s: ", error_message);
	}
	// ft_putstr_fd(strerror(errno), STDERR_FILENO);
	// ft_putstr_fd("\n", STDERR_FILENO);
	ft_printf_fd(STDERR_FILENO, "%s\n", strerror(errno));
	exit(EXIT_FAILURE);
}

void	print_error_exit(const char *error_message)
{
	ft_putstr_fd(B_RED "Error: " RESET, STDERR_FILENO);
	// ft_putstr_fd(error_message, STDERR_FILENO);
	// ft_putstr_fd("\n", STDERR_FILENO);
	ft_printf_fd(STDERR_FILENO, "%s\n", error_message);
	exit(EXIT_FAILURE);
}
