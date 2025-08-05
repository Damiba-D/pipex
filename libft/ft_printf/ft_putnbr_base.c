/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:26:49 by ddamiba           #+#    #+#             */
/*   Updated: 2025/05/05 16:31:48 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(int nb, char *base)
{
	size_t		blen;
	long		nbr;
	int			count;

	nbr = (long)nb;
	blen = ft_strlen(base);
	count = 1;
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr *= -1;
		count++;
	}
	if (nbr > (long)blen - 1)
	{
		count += ft_putnbr_base((nbr / blen), base);
	}
	ft_putchar(base[nbr % blen]);
	return (count);
}

/* int main()
{
	printf("%d\n", ft_putnbr_base(420, "01"));
	return 0;
}  */