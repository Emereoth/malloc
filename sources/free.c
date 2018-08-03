/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 14:33:23 by acottier          #+#    #+#             */
/*   Updated: 2018/08/01 14:36:00 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern t_data	g_allocations;

static void		update_zone_number(t_ctrl *new_head, int pos)
{
	int		old_nb;
	int		new_nb;
	t_ctrl	*cursor;

	old_nb = new_head->zone;
	new_nb = pos;
	cursor = new_head;
	while (cursor)
	{
		if (cursor->zone == old_nb)
			cursor->zone = new_nb;
		else
		{
			old_nb++;
			new_nb++;
			cursor->zone = new_nb;
		}
		cursor = cursor->next;
	}
}

static void		zone_purge(t_ctrl *to_free, t_ctrl *head)
{
	if (to_free->zone != 0)
	{
		if (to_free->next)
			update_zone_number(to_free->next, to_free->zone);
		while (to_free->prev && to_free->prev->zone == to_free->zone)
			to_free = to_free->prev;
		munmap(to_free, to_free->zone_size);
	}
	else
	{
		if (only_zone(to_free) == 0)
			head = NULL;
		else
		{
			head = to_free->next;
			update_zone_number(head, 0);
			while (to_free->prev && to_free->prev->zone == to_free->zone)
				to_free = to_free->prev;
			munmap(to_free, to_free->zone_size);
		}
	}
}

static void		clear_memory(t_ctrl *to_free)
{
	t_ctrl		*head;

	if (to_free->zone_size == TINY_ZONE)
		head = g_allocations.tiny;
	else if (to_free->zone_size == SMALL_ZONE)
		head = g_allocations.small;
	else
		head = g_allocations.large;
	to_free->size = 0;
	if (to_free->pos != 0 || zone_is_empty(to_free))
	{
		if (to_free->prev)
			to_free->prev->next = to_free->next;
		if (to_free->next)
			to_free->next->prev = to_free->prev;
	}
	if (zone_is_empty(to_free))
		zone_purge(to_free, head);
	to_free = NULL;

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
	return (NULL);
}

void			free(void *ptr)
{
	t_ctrl	*to_free;

	if (!ptr || !(ptr - CTRL))
		return ;
	ptr -= CTRL;
	to_free = find_memory(ptr, g_allocations.tiny);
	if (!to_free)
		to_free = find_memory(ptr, g_allocations.small);
	if (!to_free)
		to_free = find_memory(ptr, g_allocations.large);
	if (to_free)
		clear_memory(to_free);
	if (to_free && to_free->size != TINY && to_free->size != SMALL)
		munmap(to_free, to_free->size);
}
