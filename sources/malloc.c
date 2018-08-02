/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:50:45 by acottier          #+#    #+#             */
/*   Updated: 2018/08/02 15:46:08 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <stdio.h>

extern t_data	g_allocations;

void		*malloc(size_t size)
{
	init();
	if (size <= TINY)
		return (find_alloc_point(size, &g_allocations.tiny, TINY));
	else if (size <= SMALL)
		return (find_alloc_point(size, &g_allocations.small, SMALL));
	else
		return (find_alloc_point(size, &g_allocations.large, -1));
}

void		*find_alloc_point(size_t size, t_ctrl **alloc, int zone_type)
{
	t_ctrl		*cursor;
	t_ctrl		*target;

	if (!(*alloc))
	{
		*alloc = new_zone(NULL, size, zone_type);
		return (allocate(alloc, size, NULL, NULL));
	}
	cursor = *alloc;
	while (cursor)
	{
		if (available_space(cursor, size) == 0)
		{
			if (zone_type == -1)
				break ;
			target = (void*)cursor + aligned_size(cursor->size);
			return (allocate(&target, size, cursor->next, cursor));
		}
		if (!(cursor->next))
			break ;
		cursor = cursor->next;
	}
	cursor->next = new_zone(cursor, size, zone_type);
	cursor = cursor->next;
	return (allocate(&cursor, size, NULL, cursor->prev));
}

int			available_space(t_ctrl *cur, int size)
{
	int				available;

	if (cur->next && cur->next->zone == cur->zone)
	{
		available = cur->next->pos - (cur->pos + cur->size);
		if (available >= CTRL + size)
			return (0);
	}
	else
	{
		available = cur->zone_size - (cur->pos + cur->size);
		if (available >= CTRL + size)
			return (0);
	}
	return (1);
}

t_ctrl		*new_zone(t_ctrl *prev, size_t size, int zone_type)
{
	t_ctrl		*res;
	int			zone_size;

	if (zone_type == TINY)
		zone_size = TINY_ZONE;
	else if (zone_type == SMALL)
		zone_size = SMALL_ZONE;
	else
		zone_size = CTRL + size;
	res = mmap(0, zone_size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	res->size = 0;
	res->zone = (prev ? prev->zone + 1 : 0);
	res->pos = 0;
	res->zone_size = zone_size;
	res->prev = prev;
	if (prev)
		prev->next = res;
	res->next = NULL;
	return (res);
}

void		*allocate(t_ctrl **alloc_point, size_t size, t_ctrl *next,
			t_ctrl *prev)
{
	(*alloc_point)->size = CTRL + size;
	(*alloc_point)->zone = (prev ? prev->zone : 0);
	(*alloc_point)->pos = 0;
	if (prev)
	{
		(*alloc_point)->zone_size = prev->zone_size;
		if (prev->zone_size - prev->pos - prev->size >= CTRL + size)
			(*alloc_point)->pos = prev->pos + prev->size;
		else
			(*alloc_point)->zone = prev->zone + 1;
	}
	(*alloc_point)->prev = prev;
	(*alloc_point)->next = next;
	if (prev && prev != *alloc_point)
		prev->next = (*alloc_point);
	if (next && next != *alloc_point)
		next->prev = (*alloc_point);
	return ((*alloc_point + 1));
}
