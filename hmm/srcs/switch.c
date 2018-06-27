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

/*
** -lta
*/
void 				ls_lta(char **argv, t_lists *lists)
{
	int				j;
	struct stat 	fileStat;


	j = lists->argcount;
	while (j < lists->newargc)
	{
		if (j > lists->argcount && j < lists->newargc)
			write(1, "\n", 1);
		lists->i = 0;
		if(lstat(argv[j], &fileStat) < 0) 
        	ft_error("ls -l: No such file or directory");
		if (((fileStat.st_mode & S_IFMT) == S_IFREG) || S_ISLNK(fileStat.st_mode))
			ls_stat(argv[j], lists);
		else if (S_ISDIR(fileStat.st_mode) == 1)
		{
			lta_helper(lists, argv[j]);
		}
		ls_stat_helper(lists);
		free_some_stuff(lists);
		j++;
	}
}