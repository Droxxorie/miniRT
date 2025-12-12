/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_limit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:45:57 by eraad             #+#    #+#             */
/*   Updated: 2025/12/12 18:47:04 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	print_error_limit(const char *entity_name, int limit)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Exceed maximum number of ", 2);
	ft_putstr_fd(entity_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putnbr_fd(limit, 2);
	ft_putstr_fd("\n", 2);
}
