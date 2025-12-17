/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: eraad <eraad@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/01/06 12:58:26 by eraad             #+#    #+#             */
/*   Updated: 2025/01/06 12:58:26 by eraad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

// TODO add support for precision in ft_printdbl_fd
// TODO add support for %e, %g, and scientific notation
static int	ft_format(int fd, const char c, va_list args)
{
	if (c == 'c')
		return (ft_printchar_fd(va_arg(args, int), fd));
	else if (c == 's')
		return (ft_printstr_fd(va_arg(args, char *), fd));
	else if (c == 'p')
		return (ft_printaddr_fd(va_arg(args, void *), fd));
	else if (c == 'd' || c == 'i')
		return (ft_printnbr_fd(va_arg(args, int), fd));
	else if (c == 'u')
		return (ft_printunbr_fd(va_arg(args, unsigned int), fd));
	else if (c == 'x')
		return (ft_printhex_fd(va_arg(args, unsigned int), fd, 0));
	else if (c == 'X')
		return (ft_printhex_fd(va_arg(args, unsigned int), fd, 1));
	else if (c == '%')
		return (ft_printchar_fd('%', fd));
	else if (c == 'f')
		return (ft_printdbl_fd(va_arg(args, double), fd, 6));
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		temp;
	int		count;
	va_list	args;

	if (!format)
		return (-1);
	i = 0;
	temp = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			temp = ft_format(1, format[++i], args);
		else
			temp = ft_printchar_fd(format[i], 1);
		if (temp < 0)
			return (va_end(args), -1);
		count += temp;
		i++;
	}
	va_end(args);
	return (count);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	int		i;
	int		temp;
	int		count;
	va_list	args;

	if (!format)
		return (-1);
	i = 0;
	temp = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			temp = ft_format(fd, format[++i], args);
		else
			temp = ft_printchar_fd(format[i], fd);
		if (temp < 0)
			return (va_end(args), -1);
		count += temp;
		i++;
	}
	va_end(args);
	return (count);
}
