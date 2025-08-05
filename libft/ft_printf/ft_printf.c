/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:06:50 by ddamiba           #+#    #+#             */
/*   Updated: 2025/07/03 21:31:03 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handleformat(char c, va_list arg)
{
	char	*lhex;
	char	*uhex;

	lhex = "0123456789abcdef";
	uhex = "0123456789ABCDEF";
	if (c == 'c')
		return (ft_putchar(va_arg(arg, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(arg, char *)));
	else if (c == 'p')
		return (ft_putptr(va_arg(arg, void *), "0123456789abcdef"));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_base(va_arg(arg, int), "0123456789"));
	else if (c == 'u')
		return (ft_unsputnbr_base(va_arg(arg, unsigned int), "0123456789"));
	else if (c == 'x')
		return (ft_unsputnbr_base(va_arg(arg, unsigned int), lhex));
	else if (c == 'X')
		return (ft_unsputnbr_base(va_arg(arg, unsigned int), uhex));
	else if (c == '%')
		return (ft_putchar('%'));
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	arg;
	int		count;
	int		formcheck;

	i = 0;
	count = 0;
	if (format == NULL)
		return (-1);
	va_start(arg, format);
	while (format[i] != '\0')
	{
		if (format[i] != '%')
			count += ft_putchar(format[i]);
		else
		{
			formcheck = ft_handleformat(format[++i], arg);
			if (formcheck == -1)
				return (va_end(arg), -1);
			else
				count += formcheck;
		}
		i++;
	}
	return (va_end(arg), count);
}
