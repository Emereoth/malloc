/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:53:07 by acottier          #+#    #+#             */
/*   Updated: 2018/08/02 15:44:01 by acottier         ###   ########.fr       */
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
  // char  *test;

  // test = malloc(32);
  // strcpy(test, "Coucou mon Angele <3");
  // malloc(1024);
  // malloc(1024 * 32);
  // malloc(1024 * 1024);
  // malloc(1024 * 1024 * 16);
  // malloc(1024 * 1024 * 128);
  show_alloc_mem();
  allocation_dump("hexdump.log");
  return (0);
}