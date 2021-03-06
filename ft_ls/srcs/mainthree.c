/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mainthree.c                          			  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: egreen  <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/24 15:24:47 by egreen       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 20:18:23 by egreen      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../ft_ls.h"

void	main_seven(/*int argc, */char **argv, t_lists *lists)
{
	/*
	** -Rla
	*/
	if (lists->rflag == 0 && lists->tflag == 0 && \
		lists->big_r_flag > 0 && lists->lflag > 0 && \
		lists->aflag > 0)			
	{
		int j;
		j = lists->argcount - 1;
		lists->i = 0;
		while (++j < lists->newargc)
		{		
			if (j > lists->argcount && j < lists->newargc)
				write(1, "\n", 1);
			Rl_helper(argv[j], 1, lists);
			list_dirbigrl(argv[j], 1, lists);
		}
		exit (0);
	}
	/*
	** - rlt
	*/
	if (lists->rflag > 0 && lists->tflag > 0 && \
		lists->big_r_flag == 0 && lists->lflag > 0 && \
		lists->aflag == 0)			
	{
		ls_lrt(/*argc, */argv, lists);
		exit (0);
	}
}

void	main_eight(char **argv, t_lists *lists)
{
	/*
	** -rat
	*/
	if (lists->rflag > 0 && lists->tflag > 0 && \
		lists->big_r_flag == 0 && lists->lflag == 0 && \
		lists->aflag > 0)	
	{	
		ls_rat(argv, lists);
		exit (0);
	}
	/*
	** - rla
	*/
	if (lists->rflag > 0 && lists->tflag == 0 && \
		lists->big_r_flag == 0 && lists->lflag > 0 && \
		lists->aflag > 0)		
	{
		ls_lra(argv, lists);
		exit (0);
	}
	/*
	** -Rrt
	*/
	if (lists->rflag > 0 && lists->tflag > 0 && \
		lists->big_r_flag > 0 && lists->lflag == 0 && \
		lists->aflag == 0)				
	{
		int j;
		j = lists->argcount - 1;
		lists->i = 0;
		while (++j < lists->newargc)
		{		
			if (j > lists->argcount && j < lists->newargc)
				write(1, "\n", 1);
			rbigrt_helper(argv[j], 0, lists);
			rbigrt(argv[j], 0, lists);
		}
		exit (0);
	}
}

void	main_nine(char **argv, t_lists *lists)
{
	/*
	** -tal
	*/
	if (lists->rflag == 0 && lists->tflag > 0 && \
		lists->big_r_flag == 0 && lists->lflag > 0 && \
		lists->aflag > 0)	
	{
		ls_lta(argv, lists);
		exit (0);
	}
	/*
	** -Rta
	*/
	if (lists->rflag == 0 && lists->tflag > 0 && \
		lists->big_r_flag > 0 && lists->lflag == 0 && \
		lists->aflag > 0)
	{
		int j;
		j = lists->argcount - 1;
		lists->i = 0;
		while (++j < lists->newargc)
		{		
			if (j > lists->argcount && j < lists->newargc)
				write(1, "\n", 1);
			Rt_helper(argv[j], 1, lists);
			list_dirbigrt(argv[j], 1, lists);
		}
		exit (0);
	}
}

void	main_ten(/*int argc, */char **argv, t_lists *lists)
{
	/*
	** -Rlt
	*/
	if (lists->rflag == 0 && lists->tflag > 0 && \
		lists->big_r_flag > 0 && lists->lflag > 0 && \
		lists->aflag == 0)
	{
		int j;
		j = lists->argcount - 1;
		lists->i = 0;
		while (++j < lists->newargc)
		{		
			if (j > lists->argcount && j < lists->newargc)
				write(1, "\n", 1);
			rlt_helper(argv[j], 0, lists);
			rlt(argv[j], 0, lists);
		}
		exit (0);
	}
	/*
	** -Rra
	*/
	if (lists->rflag > 0 && lists->tflag == 0 && \
		lists->big_r_flag > 0 && lists->lflag == 0 && \
		lists->aflag > 0)
	{
		int j;
		j = lists->argcount - 1;
		lists->i = 0;
		while (++j < lists->newargc)
		{		
			if (j > lists->argcount && j < lists->newargc)
				write(1, "\n", 1);
			Rr_helper(argv[j], 1, lists);
			list_dirbigrr(argv[j], 1, lists);
		}
		exit (0);
	}
}

void	main_eleven(char **argv, t_lists *lists)
{
	/*
	** -Rrl
	*/
	if (lists->rflag > 0 && lists->tflag == 0 && \
		lists->big_r_flag > 0 && lists->lflag > 0 && \
		lists->aflag == 0)
	{
		int j;
		j = lists->argcount - 1;
		lists->i = 0;
		while (++j < lists->newargc)
		{		
			if (j > lists->argcount && j < lists->newargc)
				write(1, "\n", 1);
			Rrl_helper(argv[j], 0, lists);
			list_dirbigrrl(argv[j], 0, lists);
		}
		exit (0);
	}
	/*
	** -lrat
	*/
	if (lists->rflag > 0 && lists->tflag > 0 && \
		lists->big_r_flag == 0 && lists->lflag > 0 && \
		lists->aflag > 0)
	{
		ls_lrat(argv, lists);
		exit (0);
	}
}