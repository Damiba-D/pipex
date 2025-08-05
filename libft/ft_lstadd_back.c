/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:06:38 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/24 19:46:36 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

/* int main()
{
	t_list *temp;
	t_list *lst = NULL;
	t_list *lst1 = ft_lstnew("first");
	t_list *lst2 = ft_lstnew("second");
	t_list *lst3 = ft_lstnew("third");
	t_list *lst4 = ft_lstnew("fourth");

	lst1->next = NULL;
	lst2->next = NULL;
	lst3->next = NULL;
	ft_lstadd_back(&lst, lst1);
	ft_lstadd_back(&lst, lst2);
	ft_lstadd_back(&lst, lst3);
	ft_lstadd_back(&lst, lst4);
	while(lst)
		temp = lst;
		printf("%s\n", (char *)temp->content);
		lst = lst->next;
		free(temp);
	}
	return 0;
} */