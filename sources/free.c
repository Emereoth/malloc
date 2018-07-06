/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 14:33:23 by acottier          #+#    #+#             */
/*   Updated: 2018/07/06 14:20:12 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern t_data	g_allocations;

static void		clear_memory(t_ctrl *to_free)
{
	t_ctrl	*prev;
	t_ctrl	*next;

	prev = to_free->prev;
	next = to_free->next;
	if (to_free->zone_start == 0)
	{
		prev->next = next;
		next->prev = prev;
	}
}

t_ctrl			*find_memory(void *ptr, t_ctrl *alloc_list)
{
	t_ctrl	*cursor;

	cursor = alloc_list;
	while (cursor)
	{
		if ((void*)cursor == ptr)
			return (cursor);
		cursor = cursor->next;
	}
	return (cursor);
}

void			free(void *ptr)
{
	t_ctrl	*to_free;

	if (!ptr || !(ptr - CTRL))
		return ;
	ptr -= CTRL;
	ft_putstr("looking for ctrl structure at address:\n");
	show_address((void*)ptr);
	to_free = find_memory(ptr, g_allocations.tiny);
	if (!to_free)
		to_free = find_memory(ptr, g_allocations.small);
	if (!to_free)
		to_free = find_memory(ptr, g_allocations.large);
	if (to_free)
		clear_memory(to_free);
	// else
		// ft_putstr("wtf, no zone found\n");
	if (to_free && to_free->size != TINY && to_free->size != SMALL)
		munmap(to_free, to_free->size);
}
