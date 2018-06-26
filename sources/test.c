/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:53:07 by acottier          #+#    #+#             */
/*   Updated: 2018/06/26 16:37:57 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../includes/malloc.h"

int		main(void)
{
	void *	lol;

	ft_putstr("\nTEST ZONE STARTS\n\n");
	lol = ft_malloc(215);
	// show_alloc_mem();
	// ft_putstr("\n\n\n\n");
	// ft_free(lol);
	// show_alloc_mem();
	ft_putstr("\n\nTEST ZONE ENDS\n");
	return (0);
}