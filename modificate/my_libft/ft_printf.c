/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:24:53 by lmenoni           #+#    #+#             */
/*   Updated: 2025/06/04 19:32:49 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_gestish_uformat(const char *in, va_list args)
{
	if (*in == 'd' || *in == 'i')
		return (ft_printnbr(va_arg(args, int), 1));
	else if (*in == 's')
		return (ft_printstr(va_arg(args, char *), 1));
	else if (*in == 'p')
		return (ft_printpointer(va_arg(args, unsigned long), 1) + 2);
	else if (*in == 'u')
		return (ft_printunsnbr(va_arg(args, unsigned int), 1));
	else if (*in == 'x')
		return (ft_printhexa(va_arg(args, unsigned int), 1));
	else if (*in == 'X')
		return (ft_printupphexa(va_arg(args, unsigned int), 1));
	else if (*in == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	else if (*in == 'c')
	{
		ft_putchar_fd((char)va_arg(args, int), 1);
		return (1);
	}
	else
		return (-1);
}

int	ft_printf(const char *in, ...)
{
	va_list	args;
	size_t	len;

	va_start(args, in);
	len = 0;
	while (*in)
	{
		if (*in == '%')
		{
			in++;
			len += ft_gestish_uformat(in, args);
		}
		else
		{
			write (1, in, 1);
			len++;
		}
		in++;
	}
	va_end(args);
	return (len);
}
