/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:53:07 by acottier          #+#    #+#             */
/*   Updated: 2018/07/05 14:37:08 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../includes/malloc.h"

int		main(void)
{
	void *	lol;
	void *	lel;
	void *	lul;
	int		i;

	ft_putstr("\nTEST ZONE STARTS\n\n");
	i = 0;
	// while (i < 1024)
	// {
	// 	lol = ft_malloc(1024);
	// 	i++;
	// }
	lol = ft_malloc(1024);
	lel = ft_malloc(1024);
	lul = ft_malloc(1024);
	ft_putstr("\n\n\n");
	show_alloc_mem();
	ft_putstr("\n\n\n\n");
	ft_free(lel);
	show_alloc_mem();
	ft_putstr("\n\nTEST ZONE ENDS\n");
	return (0);
}