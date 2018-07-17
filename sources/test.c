/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:53:07 by acottier          #+#    #+#             */
/*   Updated: 2018/07/17 16:05:29 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../includes/malloc.h"

int		main(void)
{
	void	*lol;
	void	*lel;

	ft_putstr("\nTEST ZONE STARTS\n\n");

	lel = ft_malloc(1000000);
	lol = ft_malloc(999999);
	lel = ft_malloc(1000000);

	show_alloc_mem();

	lol = ft_realloc(lol, 1000000);

	show_alloc_mem();

	lel = ft_malloc(999999);

	show_alloc_mem();

	ft_putstr("\n\nTEST ZONE ENDS\n");
	return (0);
}
