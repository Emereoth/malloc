/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 17:23:34 by acottier          #+#    #+#             */
/*   Updated: 2018/07/06 14:19:08 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern t_data	g_allocations;

static t_ctrl	*get_memory(void *ptr)
{
	t_ctrl	*res;

	res = find_memory(ptr, g_allocations.tiny);
	if (!res)
		res = find_memory(ptr, g_allocations.small);
	if (!res)
		res = find_memory(ptr, g_allocations.large);
	return (res);
}

static int		zone_has_room(t_ctrl *target, size_t size)
{
	if ((!(target->next) || target->next->zone != target->zone)
		&& (int)(target->zone_size - (target->pos + CTRL + size)) >= 0)
		return (0);
	if (target->next && target->next->zone == target->zone
		&& (int)(target->next->pos - (target->pos + CTRL + size)) >= 0)
		return (0);
	return (1);
}

static void		*move_memory(t_ctrl *target, size_t size)
{
	t_ctrl	*new_alloc;

	if (!target)
		return (NULL);
	if (zone_has_room(target, size) == 0)
	{
		target->size = CTRL + size;
		return (target + CTRL);
	}
	new_alloc = malloc(size);
	ft_memcpy(new_alloc, target, size);
	free(target);
	return (new_alloc);
}

void			*realloc(void *ptr, size_t size)
{
	t_ctrl	*target;

	if (!ptr)
		return (malloc(size));
	ptr -= CTRL;
	if (ptr && size == 0)
	{
		free(ptr);
		return (malloc(0));
	}
	target = get_memory(ptr);
	return (move_memory(target, size));
}
