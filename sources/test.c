/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:53:07 by acottier          #+#    #+#             */
/*   Updated: 2018/07/12 15:02:35 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../includes/malloc.h"

int		main(void)
{
	void	*t1;
	void	*t2;
	void	*t3;
	void	*s1;
	void	*s2;
	void	*s3;
	void	*l1;
	void	*l2;
	void	*l3;

	ft_putstr("\nTEST ZONE STARTS\n\n");

	t1 = malloc(1025);
	t2 = malloc(1025);
	t3 = malloc(1025);
	s1 = malloc(8163);
	s2 = malloc(8163);
	s3 = malloc(8163);
	l1 = malloc(92001);
	l2 = malloc(92001);
	l3 = malloc(92001);

	t1 = realloc(t1, 2049);
	s1 = realloc(s1, 16325);
	l1 = realloc(l1, 184001);

	// free(t2);
	// free(s2);
	// free(l2);
	
	ft_putstr("\n\n");

	show_alloc_mem();

	ft_putstr("\n\nTEST ZONE ENDS\n");
	return (0);
}
