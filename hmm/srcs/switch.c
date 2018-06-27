/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   switch.c                             			  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: egreen  <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/04 12:20:13 by egreen       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 20:18:23 by egreen      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../ft_ls.h"

/*
** - swap strings
*/
void swap(char** ptr1, char** ptr2)
{
    char * temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}
		
void	ft_switch_time(t_lists *lists)
{
	lists->i = -1;
	while (++lists->i < lists->filecount)
	{
		lists->j = lists->i + 1;
		while (lists->j < lists->filecount)
		{
			if (lists->timearray[lists->i] < lists->timearray[lists->j])
			{
				ft_swap(&lists->timearray[lists->i], &lists->timearray[lists->j]);
				swap(&lists->dest[lists->i], &lists->dest[lists->j]);
			}
			else if (lists->timearray[lists->i] == lists->timearray[lists->j])
			{
				if (ft_strcmp(lists->dest[lists->i], lists->dest[lists->j]) > 0)
				{
					ft_swap(&lists->timearray[lists->i], &lists->timearray[lists->j]);
					swap(&lists->dest[lists->i], &lists->dest[lists->j]);
				}
			}
			lists->j++;
		}
	}
}
