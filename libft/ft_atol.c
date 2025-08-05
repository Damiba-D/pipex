/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:11:48 by ddamiba           #+#    #+#             */
/*   Updated: 2025/07/03 21:18:03 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_atol(const char *str)
{
	int		i;
	long	res;
	int		sign;
	char	*cpy;

	i = 0;
	res = 0;
	sign = 1;
	cpy = (char *)str;
	while (cpy[i] != '\0' && ((cpy[i] >= '\t' && cpy[i] <= '\r')
			|| cpy[i] == ' '))
		i++;
	if (cpy[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (cpy[i] == '+')
		i++;
	while ((cpy[i] != '\0' && (cpy[i] >= '0' && cpy[i] <= '9')))
	{
		res = (res * 10) + (cpy[i] - '0');
		i++;
	}
	return (res * sign);
}
