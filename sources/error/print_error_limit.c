/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_limit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:45:57 by eraad             #+#    #+#             */
/*   Updated: 2025/12/17 20:44:00 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	print_error_limit(const char *entity_name, int limit)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd("Maximum number of ", STDERR_FILENO);
	if (entity_name)
		ft_putstr_fd((char *)entity_name, STDERR_FILENO);
	ft_putstr_fd(" exceeded: ", STDERR_FILENO);
	ft_putnbr_fd(limit, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
