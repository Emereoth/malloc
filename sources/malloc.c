/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:50:45 by acottier          #+#    #+#             */
/*   Updated: 2018/06/30 18:03:48 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <stdio.h>

extern t_data	g_allocations;

void		*ft_malloc(size_t size)
{
	// t_ctrl		*alloc_point;
	
	if (size <= TINY)
	{
		// ft_putstr("\n\nTINY ALLOCATION\n");
		// alloc_point = find_alloc_point(size, &g_allocations.tiny, TINY);
		// if (!alloc_point)
			// ft_putstr("wooooooopsie\n");

		return (find_alloc_point(size, &g_allocations.tiny, TINY));
		
		// return (allocate(&alloc_point, size, alloc_point->next));
	}
	else if (size <= SMALL)
	{
		// ft_putstr("\n\nSMALL ALLOCATION\n");
		// alloc_point = find_alloc_point(size, &g_allocations.small, SMALL);
		// return (allocate(&alloc_point, size, alloc_point->next));

		return (find_alloc_point(size, &g_allocations.small, SMALL));
	}
	else
	{
		// ft_putstr("\n\nLARGE ALLOCATION\n");
		// alloc_point = find_alloc_point(size, &g_allocations.large, -1);
		// return (allocate(&alloc_point, size, alloc_point->next));

		return (find_alloc_point(size, &g_allocations.large, -1));
	}
}

void		*find_alloc_point(size_t size, t_ctrl **alloc, int zone_type)
{
	t_ctrl		*target;

	if (!(*alloc))
	{
		// ft_putstr("no alloc alloc for this size, creating one\n");
		*alloc = new_zone(NULL, size, zone_type);
		// ft_putstr("new zone address:\n");
		// show_address(*alloc);
		// return (*alloc);
		ft_putstr("this one\n");
		return (allocate(alloc, size, NULL, NULL));
	}
	while (*alloc && zone_type != -1)
	{
		if (available_space(*alloc, size) == 0)
		{
			ft_putstr("confirming available_space() addresses\n");
			show_address(*alloc);
			target = (void*)*alloc + (*alloc)->size;
			show_address(target);
			// return ((void*)*alloc + (*alloc)->size);
			ft_putstr("that one\n");
			return (allocate(&target, size, (*alloc)->next, *alloc));
		}
		// else
			// ft_putstr("no space on current zone\n");
		if (!(*alloc)->next)
			break ;
		*alloc = (*alloc)->next;
	}
	(*alloc)->next = new_zone(*alloc, size, zone_type);
	// ft_putstr("new zone address:\n");
	// show_address((*alloc)->next);
	// return (*alloc);
	ft_putstr("oooooh, THAT one\n");
	return (allocate(&((*alloc)->next), size, NULL, *alloc));
}

int			available_space(t_ctrl *cur, size_t size)
{
	t_ctrl			*next;

	ft_putstr("AVAILABLE_SPACE\ntesting zone: ");
	show_address(cur);
	while (cur)
	{
		next = cur->next;
		if (next == NULL)
		{
			if (cur->zone_size - (cur->pos + cur->size) >= CTRL + size)
			{
				ft_putstr("DEBUG 1\n");
				return (0);
			}
		}
		else
		{
			if (next->zone == cur->zone)
			{
				if (next->pos - (cur->pos + cur->size) >= CTRL + size)
				{
					ft_putstr("DEBUG 2\n");
					return (0);
				}
			}
			else
				if (cur->zone_size - (cur->pos + cur->size) >= CTRL + size)
				{
					ft_putstr("DEBUG 3\n");
					return (0);
				}
		}
		cur = next;
	}
	return (1);
}

t_ctrl		*new_zone(t_ctrl *prev, size_t size, int zone_type)
{
	t_ctrl		*res;
	int			zone_size;

	// ft_putstr("\ncreating new zone\n");
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

void		*allocate(t_ctrl **alloc_point, size_t size, t_ctrl *next, t_ctrl *prev)
{
	// t_ctrl	*last_point;

	// ft_putstr("\nALLOCATING:\n");
	(*alloc_point)->size = CTRL + size;
	(*alloc_point)->zone = prev ? prev->zone : 0;
	(*alloc_point)->zone_start = (*alloc_point)->zone_start == 1 ? 1 : 0;
	if (!prev || prev->zone != (*alloc_point)->zone)
		(*alloc_point)->pos = 0;
	else
		(*alloc_point)->pos = prev->pos + prev->size;
	if (prev)
		(*alloc_point)->zone_size = prev->zone_size;
	(*alloc_point)->prev = prev;
	(*alloc_point)->next = next;
	if (prev)
	{
		show_address(*alloc_point);
		prev->next = (*alloc_point);
		show_address(prev->next);
		if (prev->next)
			ft_putstr(" N O I C E \n");
	}
	if (next)
		next->prev = (*alloc_point);
	if (prev)
		ft_putstr("AYYYYY BOIS WE GOT A PREV\n");
	else
		ft_putstr("no prev for you, bitch\n");
	// if ((*alloc_point)->pos == 0)
	// 	(*alloc_point)->size = CTRL + size;
	// else
	// {
	// 	last_point = *alloc_point;
	// 	if ((*alloc_point)->zone_start == 0)
	// 	{
	// 		(*alloc_point) += last_point->size;
	// 		(*alloc_point)->zone_start = 0;
	// 	}
	// 	else
	// 		(*alloc_point)->zone_start = 1;
	// 	(*alloc_point)->size = CTRL + size;
	// 	(*alloc_point)->zone = last_point->zone;
	// 	(*alloc_point)->pos = last_point->pos + last_point->size;
	// 	(*alloc_point)->zone_size = last_point->zone_size;
	// 	(*alloc_point)->prev = last_point;
	// 	last_point->next = *alloc_point;
	// }
	// if (next)
	// 	next->prev = *alloc_point;
	ft_putstr("control structure address:\n");
	show_address(*alloc_point);
	ft_putstr("allocation zone address:\n");
	show_address((void*)*alloc_point + CTRL);
	ft_putstr("allocation zone end:\n");
	show_address((void*)*alloc_point + CTRL + size);
	ft_putchar('\n');
	return (((void*)alloc_point + CTRL));
}
