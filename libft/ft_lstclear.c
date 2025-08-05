/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:20:45 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/25 16:02:51 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (*lst == NULL || del == NULL)
		return ;
	temp = *lst;
	while (*lst != NULL)
	{
		temp = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(temp, del);
	}
}

/* static void del_content(void *content)
{
	free(content);
}

int main()
{
	t_list *temp;
	t_list *lst1 = ft_lstnew(ft_strdup("first"));
	t_list *lst2 = ft_lstnew(ft_strdup("second"));
	t_list *lst3 = ft_lstnew(ft_strdup("third"));
	t_list *lst4 = ft_lstnew(ft_strdup("fourth"));

	lst1->next = lst2;
	lst2->next = lst3;
	lst3->next = lst4;
	ft_lstclear(&lst2, del_content);
	while(lst1)
	{
		temp = lst1;
		printf("%s\n", (char *)temp->content);
		lst1 = lst1->next;
		free(temp);
	}
	return 0;
} */