/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:53:07 by acottier          #+#    #+#             */
/*   Updated: 2018/07/09 17:48:50 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../includes/malloc.h"

int		main(void)
{
	// void *		lol;
	void *		lel;
	// void *		lul;
	ft_putstr("\nTEST ZONE STARTS\n\n");

	// lol = ft_malloc(256);
	lel = ft_malloc(4096);
	lel = ft_realloc(lel, 1);
	// lul = ft_malloc(91556);

	show_alloc_mem();
	// ft_putstr("\n");

	// lel = realloc(lel, 512);
	// ft_putstr("\n");

	// show_alloc_mem();


	ft_putstr("\n\nTEST ZONE ENDS\n");
	return (0);
}