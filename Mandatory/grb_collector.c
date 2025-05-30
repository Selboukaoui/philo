/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grb_collector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 07:25:08 by selbouka          #+#    #+#             */
/*   Updated: 2025/05/27 18:17:56 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_all(t_collect **head)
{
	t_collect	*current;
	t_collect	*next;
	
	if (!*head || !head)
		return (NULL);
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	*head = NULL;
	return (NULL);
}

void	*ft_malloc(size_t size, int mode)
{
	static t_collect	*head;
	void				*data;
	t_collect			*node;

	data = NULL;
	node = NULL;
	if (mode == 1)
	{
		data = malloc(size);
		if (!data)
			return(ft_malloc(0, 0));
		node = malloc(sizeof(t_collect));
		if (!node)
			return(free(data), ft_malloc(0, 0));
		node->data = data;
		node->next = head;
		head = node;
	}
	else if (mode == 0)
	{
		free_all(&head);
		head = NULL;
		return (NULL);
	}
	return (data);
}
