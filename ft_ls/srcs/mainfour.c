/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mainfour.c                            			  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: egreen  <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/24 15:32:00 by egreen       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 20:18:23 by egreen      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../ft_ls.h"

void	main_twelve(char **argv, t_lists *lists)
{
	/*
	** -Rral
	*/
	if (lists->rflag > 0 && lists->tflag == 0 && \
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
			Rrl_helper(argv[j], 1, lists);
			list_dirbigrrl(argv[j], 1, lists);
		}
		exit(0);
	}
	/*
	** -Rrlt
	*/
	else if (lists->rflag > 0 && lists->tflag > 0 && \
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
			everything_helper(argv[j], 0, lists);
			// free_dest(lists);
			everything(argv[j], 0, lists);
		}
		// free_dest(lists);
		exit(0);
	}
}

void	main_thirteen(char **argv, t_lists *lists)
{
	/*
	** -Rrta
	*/
	if (lists->rflag > 0 && lists->tflag > 0 && \
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
			rbigrt_helper(argv[j], 1, lists);
			rbigrt(argv[j], 1, lists);
		}
		exit(0);
	}
	/*
	** -Rlta
	*/
	if (lists->rflag == 0 && lists->tflag > 0 && \
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
			rlt_helper(argv[j], 1, lists);
			rlt(argv[j], 1, lists);
		}
		exit(0);
	}
}

void	main_fourteen(char **argv, t_lists *lists)
{
	/*
	** - Rrlta
	*/
	if (lists->rflag > 0 && lists->tflag > 0 && \
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
			everything_helper(argv[j], 1, lists);
			everything(argv[j], 1, lists);
		}
		exit(0);
	}
}
void	main_six(/*int argc, */char **argv, t_lists *lists)
{
	/*
	** -Rr
	*/
	if (lists->rflag > 0 && lists->tflag == 0 && \
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
			lists->i = 0;
			Rr_helper(argv[j], 0, lists);
			list_dirbigrr(argv[j], 0, lists);
		}
		exit (0);
	}
	/*
	** -Rl
	*/
	if (lists->rflag == 0 && lists->tflag == 0 && \
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
			lists->i = 0;
			Rl_helper(argv[lists->argcount], 0, lists);
			list_dirbigrl(argv[lists->argcount], 0, lists);
		}
		exit (0);
	}
}