/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:50:45 by acottier          #+#    #+#             */
/*   Updated: 2018/06/20 19:32:26 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_data		g_allocations;

void		*malloc(size_t size)
{
	if (size <= TINY)
		return (find_alloc_point(size, g_allocations.tiny, TINY));
	else if (size <= SMALL)
		return (find_alloc_point(size, g_allocations.small, SMALL));
	else
		return (find_alloc_point(size, g_allocations.large, -1));
}

void		*find_alloc_point(size_t size, t_ctrl *alloc_list, int zone_type)
{
	t_ctrl		*cur;

	if (alloc_list)
		alloc_list = new_zone(NULL, size, zone_type);
	cur = alloc_list;
	while (cur && zone_type != -1)
	{
		if (available_space(cur, cur->next, size))
			return (allocate(cur, size, cur->next));
		if (!(cur->next))
			break ;
		cur = cur->next;
	}
	alloc_list = new_zone(alloc_list, size, zone_type);
	return (allocate(alloc_list, size, NULL));
}

int			available_space(t_ctrl *cur, t_ctrl *next, size_t size)
{
	if (next && cur->zone == next->zone)
		if (next->pos - (cur->pos + cur->size) >= size)
			return (0);
	if (cur->zone_size - (cur->pos + cur->size) >= size)
		return (0);
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
	res->zone_start = 1;
	res->pos = 0;
	res->zone = (prev ? prev->zone + 1 : 0);
	res->zone_size = zone_size;
	res->prev = prev;
	if (prev)
		prev->next = res;
	res->next = NULL;
	return (res);
}

void		*allocate(t_ctrl *alloc_point, size_t size, t_ctrl *next)
{
	t_ctrl	*last_point;

	if (alloc_point->pos == 0)
		alloc_point->size = CTRL + size;
	else
	{
		last_point = alloc_point;
		if (alloc_point->zone_start == 0)
		{
			alloc_point += last_point->size;
			alloc_point->zone_start = 0;
		}
		else
			alloc_point->zone_start = 1;
		alloc_point->size = CTRL + size;
		alloc_point->zone = last_point->zone;
		alloc_point->pos = last_point->pos + last_point->size;
		alloc_point->zone_size = last_point->zone_size;
		alloc_point->prev = last_point;
		last_point->next = alloc_point;
	}
	if (next)
		next->prev = alloc_point;
	return (alloc_point + CTRL);
}
