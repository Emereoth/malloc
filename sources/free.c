/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 14:33:23 by acottier          #+#    #+#             */
/*   Updated: 2018/09/24 15:27:25 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern t_data	g_allocations;

/*
** Sets allocation size to 0, links together prev and next alloc if need be.
** Unmaps the entire zone if the alloc was the last one.
*/

static void		clear_memory(t_ctrl *to_free)
{
	if (to_free->prev)
		to_free->prev->next = to_free->next;
	if (to_free->next)
		to_free->next->prev = to_free->prev;
	check_empty_zones(to_free->zone_size);
	// to_free = NULL;
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
}
