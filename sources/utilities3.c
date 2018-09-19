/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 13:35:20 by acottier          #+#    #+#             */
/*   Updated: 2018/09/19 16:53:28 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

/*
** Configures tiny and large allocation metadata with its special values. 
*/

void	setup_standard_alloc(t_ctrl *alloc, t_ctrl *prev)
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
	// ft_putstr("alloc setup over\n");
}