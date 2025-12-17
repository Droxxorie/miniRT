/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:42:00 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 07:48:24 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	log_info(const char *message)
{
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(B_GREEN "miniRT" RESET, STDOUT_FILENO);
	ft_putstr_fd("]: ", STDOUT_FILENO);
	ft_putstr_fd((char *)message, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	log_detail(const char *message, const char *detail)
{
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(B_GREEN "miniRT" RESET, STDOUT_FILENO);
	ft_putstr_fd("]: ", STDOUT_FILENO);
	ft_putstr_fd((char *)message, STDOUT_FILENO);
	if (detail)
	{
		ft_putstr_fd(UNDERLINE, STDOUT_FILENO);
		ft_putstr_fd((char *)detail, STDOUT_FILENO);
		ft_putstr_fd(RESET, STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	log_process(const char *message)
{
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(B_CYAN "miniRT" RESET, STDOUT_FILENO);
	ft_putstr_fd("]: ", STDOUT_FILENO);
	ft_putstr_fd((char *)message, STDOUT_FILENO);
	ft_putstr_fd("... ", STDOUT_FILENO);
}
