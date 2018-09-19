/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 17:23:34 by acottier          #+#    #+#             */
/*   Updated: 2018/09/19 16:52:57 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

extern t_data	g_allocations;

/*
** Searches for an existing pointer in allocated memory.
*/

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

/*
** Displaces memory to new allocation point.
*/

static void		*move_memory(t_ctrl *target, size_t size)
{
	t_ctrl	*new_alloc;
	size_t	to_copy;

	if (!target)
		return (NULL);
	if (target->zone_size <= SMALL_ZONE && available_space(target, size) == 0)
	{
		target->size = CTRL + size;
		return (target + 1);
	}
	new_alloc = malloc(size);
	to_copy = (target->size >= size) ? size : target->size;
	ft_memcpy(new_alloc, target + 1, to_copy);
	// ft_putstr("rout via free\n");
	free(target + 1);
	return (new_alloc);
}

/*
** Basic realloc(). Checks the pointer's existence before reallocating.
*/

void			*realloc(void *ptr, size_t size)
{
	t_ctrl	*target;

	// ft_putstr("rin\n");
	if (!ptr)
	{
		// ft_putstr("rout via malloc\n");
		return (malloc(size));
	}
	ptr -= CTRL;
	if (ptr && size == 0)
	{
		// ft_putstr("rout via free and malloc\n");
		free(ptr + CTRL);
		return (malloc(0));
	}
	target = get_memory(ptr);
	return (move_memory(target, size));
}
