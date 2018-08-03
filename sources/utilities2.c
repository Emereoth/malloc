/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 15:56:34 by acottier          #+#    #+#             */
/*   Updated: 2018/08/02 15:42:09 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

size_t		aligned_size(size_t size)
{
	while (size % 16 != 0)
		size++;
	return (size);
}

void		show_readable(int fd, char *cursor, size_t limit)
{
	size_t		i;

	i = 0;
	write(fd, "   ", 3);
	while (limit < 16)
	{
		write(fd, "   ", 3);
		limit++;
	}
	while (i < limit)
	{
		if (*cursor > 32 && *cursor < 126)
			write(fd, cursor, 1);
		else
			write(fd, ".", 1);
		i++;
		cursor++;
	}
}

int			zone_is_empty(t_ctrl *alloc)
{
	t_ctrl	*cursor;
	int		i;

	cursor = alloc;
	i = 0;
	while (cursor && cursor->zone == alloc->zone)
	{
		if (cursor->size > 0)
			i++;
		cursor = cursor->prev;
	}
	if (i > 1)
		return (1);
	i = 0;
	cursor = alloc;
	while (cursor && cursor->zone == alloc->zone)
	{
		if (cursor->size > 0)
			i++;
		cursor = cursor->next;
	}
	if (i > 1)
		return (1);
	return (0);
}

int			only_zone(t_ctrl	*alloc)
{
	t_ctrl	*cursor;

	cursor = alloc;
	while (cursor && cursor->zone == alloc->zone)
		cursor = cursor->prev;
	if (cursor)
		return (1);
	cursor = alloc;
	while (cursor && (cursor->zone == alloc->zone || cursor->size == 0))
		cursor = cursor->next;
	if (cursor)
		return (1);
	return (0);
}

void		init(void)
{
	static int	tiny = 0;
	static int	small = 0;
	static int	large = 0;
	
	if (tiny == 0)
	{
		g_allocations.tiny = NULL;
		tiny++;
	}
	if (small == 0)
	{
		g_allocations.small = NULL;
		small++;
	}
	if (large == 0)
	{
		g_allocations.large = NULL;
		large++;
	}
	return ;
}
