/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:19:42 by eraad             #+#    #+#             */
/*   Updated: 2026/01/08 16:33:34 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt_bonus.h>

void	sys_print_error(const char *error_message)
{
	int		saved_errno;
	char	buffer[256];

	saved_errno = errno;
	sprintf(buffer, "%s: %s", error_message, strerror(saved_errno));
	log_event(stderr, "SYSTEM ERROR", buffer);
}

void	print_error_detail(const char *error_message, const char *detail)
{
	char	buffer[256];

	sprintf(buffer, "%s: %s", error_message, detail);
	log_event(stderr, "ERROR", buffer);
}

void	print_error(const char *error_message)
{
	log_event(stderr, "ERROR", (char *)error_message);
}
