/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 17:23:34 by acottier          #+#    #+#             */
/*   Updated: 2018/07/10 17:05:04 by acottier         ###   ########.fr       */
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

static void		*move_memory(t_ctrl *target, size_t size)
{
	t_ctrl	*new_alloc;

	if (!target)
		return (NULL);
	if (available_space(target, size) == 0)
	{
		target->size = CTRL + size;
		return (target + 1);
	}
	new_alloc = malloc(size);
	ft_memcpy(new_alloc, target, size);
	ft_putchar('\n');
	free(target + 1);
	ft_putstr("REALLOC OUT\n");
	return (new_alloc);
}

void			*realloc(void *ptr, size_t size)
{
	t_ctrl	*target;

	ft_putstr("REALLOC IN: ");
	ft_putnbr(size);
	ft_putchar(' ');
	if (!ptr)
	{
		ft_putstr("\nREALLOC OUT\n");
		return (malloc(size));
	}
	show_address(ptr);
	ptr -= CTRL;
	if (ptr && size == 0)
	{
		free(ptr);
		ft_putstr("REALLOC OUT\n");
		return (malloc(0));
	}
	target = get_memory(ptr);
	return (move_memory(target, size));
}
