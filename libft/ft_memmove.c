/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:16:48 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/25 11:56:20 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*src_cpy;
	char	*dst_cpy;
	size_t	i;

	src_cpy = (char *)src;
	dst_cpy = (char *)dst;
	i = 0;
	if (dst_cpy > src_cpy)
	{
		while (len-- > 0)
			dst_cpy[len] = src_cpy[len];
	}
	else
	{
		while (i < len)
		{
			dst_cpy[i] = src_cpy[i];
			i++;
		}
	}
	return (dst);
}
