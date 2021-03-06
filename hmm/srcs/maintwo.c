/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   maintwo.c                             			  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: egreen  <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/06/24 15:18:28 by egreen       #+#   ##    ##    #+#       */
/*   Updated: 2018/06/26 20:18:23 by egreen      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../ft_ls.h"

void	the_start(int argc, char **argv, t_lists *lists)
{
	/*
	** -r
	*/
	if (lists->rflag > 0 && lists->tflag == 0 && \
		lists->big_r_flag == 0 && lists->lflag == 0 && \
		lists->aflag == 0)
		{
			list_dirr(argc, argv, lists);
			exit (0);
		}
	main_two(argc, argv, lists);
	main_three(/*argc, */argv, lists);
	main_four(/*argc, */argv, lists);
	main_five(argc, argv, lists);
	main_six(/*argc, */argv, lists);
	main_seven(/*argc, */argv, lists);
	main_eight(argv, lists);
	main_nine(argv, lists);
	main_ten(/*argc, */argv, lists);
	main_eleven(argv, lists);
	main_twelve(argv, lists);
	main_thirteen(argv, lists);
	main_fourteen(argv, lists);
}


void	main_two(int argc, char **argv, t_lists *lists)
{
	/*
	** -t
	*/
 	if (lists->rflag == 0 && lists->tflag > 0 && \
		lists->big_r_flag == 0 && lists->lflag == 0 && \
		lists->aflag == 0)
 	{
		list_dirt(argc, argv, lists);
		exit (0);
 	}
	/*
	** -a
	*/
	else if (lists->rflag == 0 && lists->tflag == 0 && \
		lists->big_r_flag == 0 && lists->lflag == 0 && \
		lists->aflag > 0)
		{
			list_dira(argc, argv, lists);
			exit (0);
		}		
	/*
	** -l
	*/
	else if (lists->rflag == 0 && lists->tflag == 0 && \
		lists->big_r_flag == 0 && lists->lflag > 0 && \
		lists->aflag == 0)		
	{
		list_dirl(argc, argv, lists);
		exit (0);

	}
	/*
	** -R
	*/
	else if (lists->rflag == 0 && lists->tflag == 0 && \
		lists->big_r_flag > 0 && lists->lflag == 0 && \
		lists->aflag == 0)	
	{
		if (argc == 2)
		{
		    argv[2] = ".";
		    argc = 3;
		}
		lists->i = 0;
		R_first(argc, argv, 0, lists->argcount);
		list_dirbigr(argv[2], 0);
		exit (0);
	}
}

void	main_three(/*int argc, */char **argv, t_lists *lists)
{
	/*
	** -la
	*/
	if (lists->rflag == 0 && lists->tflag == 0 && \
		lists->big_r_flag == 0 && lists->lflag > 0 && \
		lists->aflag > 0)			
	{
		ls_la(/*argc, */argv, lists);
		exit (0);
	}
	/*
	** -at
	*/
	else if (lists->rflag == 0 && lists->tflag > 0 && \
		lists->big_r_flag == 0 && lists->lflag == 0 && \
		lists->aflag > 0)	
	{
		list_dirta(/*argc, */argv, lists);
			exit (0);
	}
	/*
	** -tl
	*/
	else if (lists->rflag == 0 && lists->tflag > 0 && \
		lists->big_r_flag == 0 && lists->lflag > 0 && \
		lists->aflag == 0)	
	{
		ls_lt(/*argc, */argv, lists);
		exit (0);
	}
}

void	main_four(/*int argc, */char **argv, t_lists *lists)
{
	/*
	** -ra
	*/
	if (lists->rflag > 0 && lists->tflag == 0 && \
		lists->big_r_flag == 0 && lists->lflag == 0 && \
		lists->aflag > 0)	
	{
		ls_ra(/*argc, */argv, lists);
		exit (0);
	}	
	/*
	** -rt
	*/
	if (lists->rflag > 0 && lists->tflag > 0 && \
		lists->big_r_flag == 0 && lists->lflag == 0 && \
		lists->aflag == 0)	
	{
		ls_rt(/*argc, */argv, lists);
		exit (0);
	}
	/*
	** -rl
	*/
	if (lists->rflag > 0 && lists->tflag == 0 && \
		lists->big_r_flag == 0 && lists->lflag > 0 && \
		lists->aflag == 0)			
	{
		list_dirlr(/*argc, */argv, lists);
		exit (0);
	}
}

void	main_five(int argc, char **argv, t_lists *lists)
{
	/*
	** -Ra
	*/
	if (lists->rflag == 0 && lists->tflag == 0 && \
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
			lists->i = 0;
			R_first(argc, argv, 1, lists->argcount);
			list_dirbigr(argv[lists->argcount], 1);
		}
		exit (0);
	}
	/*
	** -Rt
	*/
	if (lists->rflag == 0 && lists->tflag > 0 && \
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
			Rt_helper(argv[lists->argcount], 0, lists);
			list_dirbigrt(argv[lists->argcount], 0, lists);
		}
		exit (0);
	}
}

