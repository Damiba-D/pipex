/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:19:37 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/25 16:44:40 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp2;
	t_list	*newlst;

	if (lst == NULL || del == NULL || f == NULL)
		return (NULL);
	temp2 = NULL;
	while (lst)
	{
		newlst = (t_list *)malloc(sizeof(t_list));
		if (newlst == NULL)
		{
			ft_lstclear(&temp2, del);
			return (NULL);
		}
		newlst->content = f(lst->content);
		newlst->next = NULL;
		ft_lstadd_back(&temp2, newlst);
		lst = lst->next;
	}
	return (temp2);
}

/* static void del_content(void *content)
{
	free(content);
}

static void *map_toupper(void *content)
{
	if (*((char *)content) >= 'a' && *((char *)content) <= 'z')
		*((char *)content) -= 32;
	return (content);
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
	temp = ft_lstmap(lst1, map_toupper, del_content);
	while(temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	ft_lstclear(&temp, del_content);
	ft_lstclear(&lst1, del_content);
	return 0;
} */
