/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:15:27 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/24 16:37:28 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_SPLIT_H
# define ARG_SPLIT_H
# include "../pipex.h"

char			**arg_split(char *s, int *inv_arg);
int				ft_cpy_alloc(char **arr, char *s);
unsigned int	count_args(char *s);
void			arg_len(char *s, int *i, int *len);
#endif