/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 13:35:20 by acottier          #+#    #+#             */
/*   Updated: 2018/09/24 15:34:28 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/*
** Configures tiny and large allocation metadata with its special values.
*/

void			setup_standard_alloc(t_ctrl *alloc, t_ctrl *prev)
{
	t_ctrl	*cursor;

	if (!prev)
		alloc->pos = 0;
	else
	{
		if (prev->zone_size - prev->pos - prev->size >= alloc->size)
		{
			alloc->zone = prev->zone;
			alloc->pos = prev->pos + prev->size;
			cursor = prev;
			while (cursor->prev && cursor->prev->zone == alloc->zone)
				cursor = cursor->prev;
			alloc->zone_start = cursor;
		}
		else
		{
			alloc->zone = prev->zone + 1;
			alloc->pos = 0;
			alloc->zone_start = alloc;
		}
		alloc->zone_size = prev->zone_size;
	}
}

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
		if (to_free->next)
			update_zone_number(to_free->next, to_free->zone);
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
		update_zone_number(to_free->next, 0);
		munmap(to_free->zone_start, to_free->zone_size);
	}
}

/*
** Goes straight to head alloc of next zone
*/

t_ctrl			*next_zone(t_ctrl *alloc)
{
	unsigned char zone;

	zone = alloc->zone;
	while (alloc && alloc->zone == zone)
		alloc = alloc->next;
	return (alloc);
}

/*
** Walks througgh alloc zones looking for more than 1 empty zone.
*/

void			check_empty_zones(size_t zone_size)
{
	t_ctrl	*alloc;
	t_ctrl	*buffer_zone;
	size_t	empties;

	if (zone_size == TINY_ZONE)
		alloc = g_allocations.tiny;
	else if (zone_size == SMALL_ZONE)
		alloc = g_allocations.small;
	else
		return ;
	empties = 0;
	buffer_zone = NULL;
	while (alloc)
	{
		if (zone_is_empty(alloc) == 0 && !buffer_zone)
			buffer_zone = alloc;
		else if (zone_is_empty(alloc) == 0 && buffer_zone)
			zone_purge(alloc);
		alloc = next_zone(alloc);
	}
}
