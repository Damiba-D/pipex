/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:27:43 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/25 16:45:04 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	if (lst == NULL || f == NULL)
		return ;
	temp = lst;
	while (lst)
	{
		temp = lst;
		f(temp->content);
		lst = lst->next;
	}
}
/* static void content_print(void *content)
{
	printf("%s\n",(char *)content);
}

 int main()
{
	t_list *temp;
	t_list *lst1 = ft_lstnew("first");
	t_list *lst2 = ft_lstnew("second");
	t_list *lst3 = ft_lstnew("third");

	lst1->next = lst2;
	lst2->next = lst3;
	lst3->next = NULL;
	ft_lstiter(lst1, content_print);
	while(lst1)
	{
		temp = lst1;
		// printf("%s\n", (char *)temp->content);
		lst1 = lst1->next;
		free(temp);
	}
	return 0;
} */