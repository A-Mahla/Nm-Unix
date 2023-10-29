/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:31:02 by amahla            #+#    #+#             */
/*   Updated: 2022/05/02 12:31:05 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static t_list	*ft_lstnew2(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

static void	ft_lstclear2(t_list **lst, void (*del)(void *))
{
	t_list	*elem;
	t_list	*next;

	elem = *lst;
	while (elem)
	{
		next = elem->next;
		(*del)(elem->content);
		free(elem);
		elem = next;
	}
	*lst = NULL;
}

static void	ft_lstadd_back2(t_list **lst, t_list *new)
{
	t_list	*elem;

	elem = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (elem->next)
			elem = elem->next;
		elem->next = new;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*elem;
	t_list	*begin_lst;

	begin_lst = NULL;
	elem = NULL;
	while (lst)
	{
		elem = ft_lstnew2((*f)(lst->content));
		if (!elem)
		{
			ft_lstclear2(&begin_lst, del);
			return (NULL);
		}
		ft_lstadd_back2(&begin_lst, elem);
		lst = lst->next;
	}
	return (begin_lst);
}
