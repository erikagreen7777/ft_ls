#include "../ft_ls.h"

void	main_seven(int argc, char **argv, t_lists *lists)
{
	/*
	** -Rla
	*/
	if (lists->rflag == 0 && lists->tflag == 0 && \
		lists->big_r_flag > 0 && lists->lflag > 0 && \
		lists->aflag > 0)			
	{
		if (argc == 2)
		{
		    argv[2] = ".";
		    argc = 3;
		}
		lists->i = 0;
		Rl_helper(argv[2], 1, lists);
		list_dirbigrl(argv[2], 1, lists);
		exit (0);
	}
	/*
	** - rlt
	*/
	if (lists->rflag > 0 && lists->tflag > 0 && \
		lists->big_r_flag == 0 && lists->lflag > 0 && \
		lists->aflag == 0)			
	{
		ls_lrt(argc, argv, lists);
		exit (0);
	}
}

void	main_eight(int argc, char **argv, t_lists *lists)
{
	/*
	** -rat
	*/
	if (lists->rflag > 0 && lists->tflag > 0 && \
		lists->big_r_flag == 0 && lists->lflag == 0 && \
		lists->aflag > 0)	
	{	
		ls_rat(argc, argv, lists);
		exit (0);
	}
	/*
	** - rla
	*/
	if (lists->rflag > 0 && lists->tflag == 0 && \
		lists->big_r_flag == 0 && lists->lflag > 0 && \
		lists->aflag > 0)		
	{
		ls_lra(argc, argv, lists);
		exit (0);
	}
	/*
	** -Rrt
	*/
	if (lists->rflag > 0 && lists->tflag > 0 && \
		lists->big_r_flag > 0 && lists->lflag == 0 && \
		lists->aflag == 0)				
	{
		if (argc == 2)
		{
		    argv[2] = ".";
		    argc = 3;
		}
		lists->i = 0;
		rbigrt_helper(argv[2], 0, lists);
		rbigrt(argv[2], 0, lists);
		exit (0);
	}
}

void	main_nine(int argc, char **argv, t_lists *lists)
{
	/*
	** -tal
	*/
	if (lists->rflag == 0 && lists->tflag > 0 && \
		lists->big_r_flag == 0 && lists->lflag > 0 && \
		lists->aflag > 0)	
	{
		ls_lta(argc, argv, lists);
		exit (0);
	}
	/*
	** -Rta
	*/
	if (lists->rflag == 0 && lists->tflag > 0 && \
		lists->big_r_flag > 0 && lists->lflag == 0 && \
		lists->aflag > 0)
	{
		if (argc == 2)
		{
		    argv[2] = ".";
		    argc = 3;
		}
		lists->i = 0;
		Rt_helper(argv[2], 1, lists);
		list_dirbigrt(argv[2], 1, lists);
		exit (0);
	}
}

void	main_ten(int argc, char **argv, t_lists *lists)
{
	/*
	** -Rlt
	*/
	if (lists->rflag == 0 && lists->tflag > 0 && \
		lists->big_r_flag > 0 && lists->lflag > 0 && \
		lists->aflag == 0)
	{
		if (argc == 2)
		{
		    argv[2] = ".";
		    argc = 3;
		}
		lists->i = 0;
		rlt_helper(argv[2], 0, lists);
		rlt(argv[2], 0, lists);
		exit (0);
	}
	/*
	** -Rra
	*/
	if (lists->rflag > 0 && lists->tflag == 0 && \
		lists->big_r_flag > 0 && lists->lflag == 0 && \
		lists->aflag > 0)
	{
		if (argc == 2)
		{
		    argv[2] = ".";
		    argc = 3;
		}
		lists->i = 0;
		Rr_helper(argv[2], 1, lists);
		list_dirbigrr(argv[2], 1, lists);
		exit (0);
	}
}

void	main_eleven(int argc, char **argv, t_lists *lists)
{
	/*
	** -Rrl
	*/
	if (lists->rflag > 0 && lists->tflag == 0 && \
		lists->big_r_flag > 0 && lists->lflag > 0 && \
		lists->aflag == 0)
	{
		if (argc == 2)
		{
		    argv[2] = ".";
		    argc = 3;
		}
		lists->i = 0;
		Rrl_helper(argv[2], 0, lists);
		list_dirbigrrl(argv[2], 0, lists);
		exit (0);
	}
	/*
	** -lrat
	*/
	if (lists->rflag > 0 && lists->tflag > 0 && \
		lists->big_r_flag == 0 && lists->lflag > 0 && \
		lists->aflag > 0)
	{
		ls_lrat(argc, argv, lists);
		exit (0);
	}
}