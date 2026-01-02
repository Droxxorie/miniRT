/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:19:42 by eraad             #+#    #+#             */
/*   Updated: 2026/01/02 16:39:15 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	sys_print_error(const char *error_message)
{
	int	saved_errno;

	saved_errno = errno;
	ft_putstr_fd(B_RED "Error\n" RESET, STDERR_FILENO);
	if (error_message)
	{
		ft_putstr_fd((char *)error_message, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(strerror(saved_errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	print_error(const char *error_message)
{
	ft_putstr_fd(B_RED "Error\n" RESET, STDERR_FILENO);
	if (error_message)
		ft_putstr_fd((char *)error_message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
