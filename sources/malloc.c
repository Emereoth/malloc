/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:50:45 by acottier          #+#    #+#             */
/*   Updated: 2018/07/09 17:59:25 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <stdio.h>

extern t_data	g_allocations;

// static void	show_zones()
// {
// 	t_ctrl	*cursor;
// 	cursor = g_allocations.small;
// 	ft_putstr("SMALL:\n");
// 	if (!cursor)
// 		return ;
// 	while (cursor)
// 	{
// 		ft_putstr("CURSOR EXISTS FFS\n");
// 		if (cursor->pos == 0)
// 		{
// 			ft_putnbr(cursor->zone);
// 			ft_putstr(" zone start:\n");
// 			show_address(cursor);
// 		}
// 		if (!(cursor->next) || cursor->next->zone != cursor->zone)
// 		{
// 			ft_putnbr(cursor->zone);
// 			ft_putstr(" zone end:\n");
// 			show_address((void*)cursor + cursor->size);
// 		}
// 		cursor = cursor->next;
// 	}
// }

void		*ft_malloc(size_t size)
{
	ft_putstr("MALLOC IN ");
	ft_putnbr(size);
	ft_putchar('\n');
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
		// ft_putstr("no alloc for this size, creating one\n");
		*alloc = new_zone(NULL, size, zone_type);
		// ft_putstr("new zone address:\n");
		// show_address(*alloc);
		return (allocate(alloc, size, NULL, NULL));
	}
	cursor = *alloc;
	while (cursor)
	{
		if (zone_type != -1 && available_space(cursor, size) == 0)
		{
			// ft_putstr("\nconfirming available_space() addresses\n");
			// show_address(cursor);
			if (cursor->pos + cursor->size > cursor->zone_size + size)
				break ;
			target = (void*)cursor + cursor->size;
			// show_address(target);
			return (allocate(&target, size, cursor->next, cursor));
		}
		if (!(cursor->next))
			break ;
		cursor = cursor->next;
	}
	show_address(cursor);
	cursor->next = new_zone(cursor, size, zone_type);
	// ft_putstr("new zone address:\n");
	// show_address(cursor->next);
	return (allocate(&(cursor->next), size, NULL, cursor));
}

int			available_space(t_ctrl *cur, size_t size)
{
	t_ctrl			*next;

	// ft_putstr("AVAILABLE_SPACE\ntesting zone: ");
	// show_address(cur);
	next = cur->next;
	if (next == NULL)
	{
		if (cur->zone_size - (cur->pos + cur->size) >= CTRL + size)
			return (0);
	}
	else
	{
		if (next->zone == cur->zone)
		{
			if (next->pos - (cur->pos + cur->size) >= CTRL + size)
				return (0);
		}
		else
			if (cur->zone_size - (cur->pos + cur->size) >= CTRL + size)
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
		// ft_putstr("prev control structure:\n");
		// show_address(prev);
		prev->next = (*alloc_point);
	}
	if (next)
	{
		// ft_putstr("next control structure:\n");
		// show_address(next);
		next->prev = (*alloc_point);
	}
	// ft_putstr("control structure address:\n");
	// show_address(*alloc_point);
	// ft_putstr("allocation zone address:\n");
	// show_address(*alloc_point + 1);
	// ft_putstr("allocation zone end:\n");
	// show_address((void*)*alloc_point + CTRL + size);
	// show_zones();
	// ft_putstr("MALLOC OUT\n");
	return ((*alloc_point + 1));
}
