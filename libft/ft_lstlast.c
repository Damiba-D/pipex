/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:53:04 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/24 19:32:21 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (lst == NULL)
		return (lst);
	temp = lst;
	while (temp->next)
	{
		temp = temp->next;
	}
	return (temp);
}

/* int main()
{
	t_list *temp;
	t_list *last;
	t_list *lst1 = ft_lstnew("first");
	t_list *lst2 = ft_lstnew("second");
	t_list *lst3 = ft_lstnew("third");
	t_list *lst0 = ft_lstnew("zero");

	lst1->next = lst2;
	lst2->next = lst3;
	lst3->next = NULL;
	ft_lstadd_front(&lst1, lst0);
	last = ft_lstlast(lst0);
	printf("%s\n", (char *)last->content);
	while(lst0)
	{
		temp = lst0;
		lst0 = lst0->next;
		free(temp);
	}
	return 0;
} */