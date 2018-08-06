/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:53:07 by acottier          #+#    #+#             */
/*   Updated: 2018/08/06 18:09:34 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>
#include <stdlib.h>
#include "../includes/malloc.h"

#define M (1024 * 1024) 

void print(char *s) 
{ 
  write(1, s, strlen(s)); 
} 

int main() 
{ 
  int i; 
  char *addr; 

  i = 0; 
  while (i < 1024) 
  {
  // ft_putnbr(i);
   addr = (char*)malloc(1024); 
   addr[0] = 42; 
   free(addr); 
   i++; 
  } 
  return (0); 
} 