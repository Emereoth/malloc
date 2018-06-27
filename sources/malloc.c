/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:50:45 by acottier          #+#    #+#             */
/*   Updated: 2018/06/27 17:02:20 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <stdio.h>

extern t_data	g_allocations;

void		*ft_malloc(size_t size)
{
	t_ctrl		**alloc_point;
	
	if (size <= TINY)
	{
		ft_putstr("\n\nTINY ALLOCATION\n");
		alloc_point = find_alloc_point(size, &g_allocations.tiny, TINY);
		
		return (allocate(alloc_point, size, (*alloc_point)->next));
	}
	else if (size <= SMALL)
	{
		ft_putstr("\n\nSMALL ALLOCATION\n");
		alloc_point = find_alloc_point(size, &g_allocations.small, SMALL);
		return (allocate(alloc_point, size, (*alloc_point)->next));
	}
	else
	{
		ft_putstr("\n\nLARGE ALLOCATION\n");
		alloc_point = find_alloc_point(size, &g_allocations.large, -1);
		return (allocate(alloc_point, size, (*alloc_point)->next));
	}
}

t_ctrl		**find_alloc_point(size_t size, t_ctrl **alloc_list, int zone_type)
{
	t_ctrl		**tmp;

	if (!(*alloc_list))
	{
		ft_putstr("no alloc list for this size, creating one\n");
		*alloc_list = new_zone(NULL, size, zone_type);
		ft_putstr("new zone address:\n");
		show_address(alloc_list);
		return (alloc_list);
	}
	while (*alloc_list && zone_type != -1)
	{
		if (available_space(alloc_list, (*alloc_list)->next, size) == 0)
		{
			ft_putstr("confirming available_space() addresses\n");
			show_address(alloc_list);
			tmp = alloc_list + (*alloc_list)->size;
			show_address(tmp);
			return ((void*)alloc_list + (void*)((*alloc_list)->size);
		}
		else
			ft_putstr("no space on current zone\n");
		if (!(*alloc_list)->next)
			break ;
		*alloc_list = (*alloc_list)->next;
	}
	(*alloc_list)->next = new_zone(*alloc_list, size, zone_type);
	ft_putstr("new zone address:\n");
	show_address(alloc_list);
	return (alloc_list);
}

int			available_space(t_ctrl **cur, t_ctrl *next, size_t size)
{
	t_ctrl		**tmp;

	ft_putstr("AVAILABLE_SPACE\ntesting zone: ");
	show_address(cur);
	if (next && (*cur)->zone == next->zone)
		if (next->pos - ((*cur)->pos + (*cur)->size) >= size)
			return (0);
	if ((*cur)->zone_size - ((*cur)->pos + (*cur)->size) >= size)
	{
		show_address(cur);
		ft_putstr("->\n");
		tmp = cur + (*cur)->size;
		show_address(tmp);
		ft_putchar('\n');
		return (0);
	}
	return (1);
}

t_ctrl		*new_zone(t_ctrl *prev, size_t size, int zone_type)
{
	t_ctrl		*res;
	int			zone_size;

	ft_putstr("\ncreating new zone\n");
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

void		*allocate(t_ctrl **alloc_point, size_t size, t_ctrl *next)
{
	t_ctrl	*last_point;

	if ((*alloc_point)->pos == 0)
		(*alloc_point)->size = CTRL + size;
	else
	{
		last_point = *alloc_point;
		if ((*alloc_point)->zone_start == 0)
		{
			(*alloc_point) += last_point->size;
			(*alloc_point)->zone_start = 0;
		}
		else
			(*alloc_point)->zone_start = 1;
		(*alloc_point)->size = CTRL + size;
		(*alloc_point)->zone = last_point->zone;
		(*alloc_point)->pos = last_point->pos + last_point->size;
		(*alloc_point)->zone_size = last_point->zone_size;
		(*alloc_point)->prev = last_point;
		last_point->next = *alloc_point;
	}
	if (next)
		next->prev = *alloc_point;
	ft_putstr("control structure address:\n");
	show_address(alloc_point);
	ft_putstr("allocation zone address:\n");
	show_address(alloc_point + CTRL);
	return (*(alloc_point + CTRL));
}
