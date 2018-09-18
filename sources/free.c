/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 14:33:23 by acottier          #+#    #+#             */
/*   Updated: 2018/09/18 15:53:16 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern t_data	g_allocations;

/*
** Updates zone numbers in the event of a zone purge.
*/

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

/*
** Unmaps zone and moves alloc list head if necessary.
*/

static void		zone_purge(t_ctrl *to_free)
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
		if (only_zone(to_free) != 0)
		{
			ft_putstr("to_free->next : ");
			show_address(to_free->next);
			ft_putstr("to_free->prev : ");
			show_address(to_free->prev);
			// *head = *(to_free->next);
			if (to_free->zone_size == TINY_ZONE)
				g_allocations.tiny = to_free->next;
			else if (to_free->zone_size == SMALL_ZONE)
				g_allocations.small = to_free->next;
			else
				g_allocations.large = to_free->next;
			ft_putstr("updated heads:\n");
			show_address(g_allocations.tiny);
			show_address(g_allocations.small);
			show_address(g_allocations.large);
			// update_zone_number(heads[head_index], 0);
			while (to_free->prev && to_free->prev->zone == to_free->zone)
				to_free = to_free->prev;
			munmap(to_free, to_free->zone_size);
		}
	}
}

/*
** Sets allocation size to 0, links together prev and next alloc if need be.
** Unmaps the entire zone if the alloc was the last one.
*/

static void		clear_memory(t_ctrl *to_free)
{
	ft_putstr("Clearing memory segment.\n");
	if (to_free->pos != 0 || zone_is_empty(to_free) == 1)
	{
		if (to_free->prev)
			to_free->prev->next = to_free->next;
		if (to_free->next)
			to_free->next->prev = to_free->prev;
	}
	if (zone_is_empty(to_free) == 0)
	{
		zone_purge(to_free);
		ft_putstr("Zone purged.\n");
		return ;
	}
	if (to_free->pos != 0)
	{
		ft_putstr("Alloc is not at zone start, setting pointer to NULL.\n");
		to_free = NULL;
	}
	else
	{
		ft_putstr("Alloc is at zone start, reducing alloc size to CTRL.\n");
		to_free->size = CTRL;
	}
}

/*
** Walks through allocated memory to check if passed pointer exists and is in use.
*/

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

/*
** Basic free() function. Checks if the pointer exists and is valid before freeing.
*/

void			free(void *ptr)
{
	t_ctrl	*to_free;

	ft_putstr("fin\n");
	if (!ptr || !(ptr - CTRL))
	{
		ft_putstr("fout\n");
		return ;
	}
	ft_putstr("pointer exists and is valid: ");
	show_address(ptr);
	ptr -= CTRL;
	to_free = find_memory(ptr, g_allocations.tiny);
	if (!to_free)
		to_free = find_memory(ptr, g_allocations.small);
	if (!to_free)
		to_free = find_memory(ptr, g_allocations.large);
	if (to_free)
		clear_memory(to_free);
	ft_putstr("fout\n");
}
