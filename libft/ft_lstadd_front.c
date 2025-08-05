/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:17:28 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/26 17:00:36 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL || lst == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

/* int main()
{
	// t_list *temp;
	t_list **head = NULL;
	// t_list *lst1 = ft_lstnew("first");
	// t_list *lst2 = ft_lstnew("second");
	// t_list *lst3 = ft_lstnew("third");
	t_list *lst0 = ft_lstnew("zero");

	// lst1->next = lst2;
	// lst2->next = lst3;
	// lst3->next = NULL;
	ft_lstadd_front(head, lst0);
	printf("bom dia???\n");
	printf("%s\n", (char *)(*head)->content);
	// printf("%s\n", (char *)lst0->next);
	// printf("%s\n", (char *)lst0->next->next->next->content);
	// while(lst0)
	// {
	// 	temp = lst0;
	// 	lst0 = lst0->next;
	// 	free(temp);
	// }
	return 0;
} */