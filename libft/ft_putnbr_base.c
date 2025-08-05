/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:26:49 by ddamiba           #+#    #+#             */
/*   Updated: 2025/05/01 16:08:02 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(int nb, char *base)
{
	int		blen;
	long	nbr;

	nbr = (long)nb;
	blen = strlen(base);
	if (nbr < 0)
	{
		ft_putchar_fd('-', 1);
		nbr *= -1;
	}
	if (nbr > blen - 1)
	{
		ft_putnbr_base((nbr / blen), base);
	}
	ft_putchar_fd(base[nbr % blen], 1);
	return ;
}

/* int main()
{
	ft_putnbr_base(-2147483648, "01");
	printf("\n");
	return 0;
}  */