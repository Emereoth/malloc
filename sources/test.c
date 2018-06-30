/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:53:07 by acottier          #+#    #+#             */
/*   Updated: 2018/06/30 17:35:34 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../includes/malloc.h"

int		main(void)
{
	void *	lol;
	int		i;

	ft_putstr("\nTEST ZONE STARTS\n\n");
	i = 0;
	// while (i < 4)
	// {
	// 	lol = ft_malloc(1024);
	// 	i++;
	// }
	lol = ft_malloc(1024);
	lol = ft_malloc(1024);
	lol = ft_malloc(1024);
	ft_putstr("\n\n\n");
	// show_alloc_mem();
	// ft_putstr("\n\n\n\n");
	// ft_free(lol);
	// show_alloc_mem();
	ft_putstr("\n\nTEST ZONE ENDS\n");
	return (0);
}