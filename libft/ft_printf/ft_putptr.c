/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:31:20 by ddamiba           #+#    #+#             */
/*   Updated: 2025/05/05 17:22:41 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr_add(unsigned long nb, char *base)
{
	size_t		blen;
	int			count;

	blen = ft_strlen(base);
	count = 1;
	if (nb > blen - 1)
	{
		count += ft_putptr_add((nb / blen), base);
	}
	ft_putchar(base[nb % blen]);
	return (count);
}

int	ft_putptr(void *ptr, char *base)
{
	size_t			blen;
	unsigned long	nbr;
	int				count;

	nbr = (unsigned long)ptr;
	if (nbr == 0)
		return (ft_putstr("(nil)"));
	blen = ft_strlen(base);
	count = 1;
	count += ft_putstr("0x");
	if (nbr > blen - 1)
	{
		count += ft_putptr_add((nbr / blen), base);
	}
	ft_putchar(base[nbr % blen]);
	return (count);
}
