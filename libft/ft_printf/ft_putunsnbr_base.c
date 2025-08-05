/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsnbr_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:26:49 by ddamiba           #+#    #+#             */
/*   Updated: 2025/05/05 17:04:45 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsputnbr_base(unsigned int nb, char *base)
{
	size_t				blen;
	unsigned long long	nbr;
	int					count;

	nbr = (unsigned long long)nb;
	blen = ft_strlen(base);
	count = 1;
	if (nbr > blen - 1)
	{
		count += ft_unsputnbr_base((nbr / blen), base);
	}
	ft_putchar(base[nbr % blen]);
	return (count);
}

/* int main()
{
	printf("%d\n", ft_putnbr_base(420, "01"));
	return 0;
}  */