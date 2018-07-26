/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 14:33:23 by acottier          #+#    #+#             */
/*   Updated: 2018/07/26 11:45:59 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern t_data	g_allocations;

static void		clear_memory(t_ctrl *to_free)
{
	to_free->size = 0;
	// if (to_free->zone_size != TINY_ZONE && to_free->zone_size != SMALL_ZONE)
	// {
	// 	if (to_free->prev)
	// 		to_free->prev->next = to_free->next;
	// 	if (to_free->next)
	// 		to_free->next->prev = to_free->prev;
	// 	return ;
	// }
	if (to_free->pos != 0)
	{
		if (to_free->prev)
			to_free->prev->next = to_free->next;
		if (to_free->next)
			to_free->next->prev = to_free->prev;
		to_free = NULL;
	}
}

t_ctrl			*find_memory(void *ptr, t_ctrl *alloc_list)
{
	t_ctrl	*cursor;

	cursor = alloc_list;
	while (cursor)
	{
		// if (cursor == cursor->next)
			// return (NULL);
		if ((void*)cursor == ptr)
		{
			// ft_putstr("found memory\n");
			return (cursor);
		}
		cursor = cursor->next;
	}
	return (NULL);
}

void			ft_free(void *ptr)
{
	t_ctrl	*to_free;

	// ft_putstr("Fin\n");
	if (!ptr || !(ptr - CTRL))
	{
		// ft_putstr("Fout 0\n");
		return ;
	}
	ptr -= CTRL;
	to_free = find_memory(ptr, g_allocations.tiny);
	if (!to_free)
		to_free = find_memory(ptr, g_allocations.small);
	if (!to_free)
		to_free = find_memory(ptr, g_allocations.large);
	// ft_putstr("target memory segment found\n");
	if (to_free)
		clear_memory(to_free);
	if (to_free && to_free->size != TINY && to_free->size != SMALL)
		munmap(to_free, to_free->size);
	// ft_putstr("Fout 1\n");
}
