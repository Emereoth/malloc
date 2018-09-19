/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 14:33:23 by acottier          #+#    #+#             */
/*   Updated: 2018/09/19 16:52:47 by acottier         ###   ########.fr       */
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

	if (!new_head)
		return ;
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
		// ft_putstr("not first zone, heads don't move\n");
		if (to_free->next)
			update_zone_number(to_free->next, to_free->zone);
		// ft_putstr("unmapping ");
		// ft_putnbr(to_free->zone_size);
		// ft_putstr(" bytes at address ");
		// show_address(to_free);
		munmap(to_free->zone_start, to_free->zone_size);
	}
	else
	{
		if (to_free->zone_size == TINY_ZONE)
			g_allocations.tiny = to_free->next;
		else if (to_free->zone_size == SMALL_ZONE)
			g_allocations.small = to_free->next;
		else
			g_allocations.large = to_free->next;
		// ft_putstr("updated heads:\n");
		// show_address(g_allocations.tiny);
		// show_address(g_allocations.small);
		// show_address(g_allocations.large);
		update_zone_number(to_free->next, 0);
		munmap(to_free->zone_start, to_free->zone_size);
	}
}

/*
** Sets allocation size to 0, links together prev and next alloc if need be.
** Unmaps the entire zone if the alloc was the last one.
*/

static void		clear_memory(t_ctrl *to_free)
{
	// ft_putstr("Clearing memory segment ");
	// show_address(to_free + 1);
	// ft_putstr("(");
	// ft_putnbr(to_free->size - CTRL);
	// ft_putstr(" bytes)\n");
	// ft_putstr("linked prev and next pointers together\n");
	if (to_free->prev)
		to_free->prev->next = to_free->next;
	if (to_free->next)
		to_free->next->prev = to_free->prev;
	// ft_putstr("prev: ");
	// show_address(to_free->prev);
	// ft_putstr("next: ");
	// show_address(to_free->next);
	if (zone_is_empty(to_free) == 0)
	{
		zone_purge(to_free);
		// ft_putstr("Zone purged.\n");
		return ;
	}
	to_free = NULL;
	// ft_putstr("Alloc set to NULL.\n");
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

	// ft_putstr("fin\n");
	if (!ptr || !(ptr - CTRL))
	{
		// ft_putstr("fout\n");
		return ;
	}
	// ft_putstr("pointer exists and is valid: ");
	// show_address(ptr);
	ptr -= CTRL;
	to_free = find_memory(ptr, g_allocations.tiny);
	if (!to_free)
		to_free = find_memory(ptr, g_allocations.small);
	if (!to_free)
		to_free = find_memory(ptr, g_allocations.large);
	if (to_free)
		clear_memory(to_free);
	// ft_putstr("fout\n");
}
