/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 14:33:23 by acottier          #+#    #+#             */
/*   Updated: 2018/07/10 17:08:21 by acottier         ###   ########.fr       */
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
		if (prev)
			prev->next = next;
		if (next)
			next->prev = prev;
	}
}

t_ctrl			*find_memory(void *ptr, t_ctrl *alloc_list)
{
	t_ctrl	*cursor;

	ft_putstr("find_memory, comparing\n");
	cursor = alloc_list;
	while (cursor)
	{
		show_address(cursor);
		if ((void*)cursor == ptr)
		{
			ft_putstr("found ya, bitch\n");
			return (cursor);
		}
		if (cursor->next)
			ft_putstr("yasss\n");
		else
			ft_putstr("no next\n");
		cursor = cursor->next;
	}
	ft_putstr("nope, done\n");
	return (cursor);
}

void			free(void *ptr)
{
	t_ctrl	*to_free;

	ft_putstr("FREE IN\n");
	// show_alloc_mem();
	if (!ptr || !(ptr - CTRL))
	{
		ft_putstr("FREE OUT\n");
		return ;
	}
	ft_putstr("free target:\n");
	show_address(ptr);
	ptr -= CTRL;
	show_address(ptr);
	to_free = find_memory(ptr, g_allocations.tiny);
	to_free = NULL;
	if (!to_free)
		to_free = find_memory(ptr, g_allocations.small);
	if (!to_free)
		to_free = find_memory(ptr, g_allocations.large);
	if (to_free)
		clear_memory(to_free);
	if (to_free && to_free->size != TINY && to_free->size != SMALL)
		munmap(to_free, to_free->size);
	ft_putstr("FREE OUT\n");
}
