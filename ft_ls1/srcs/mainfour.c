#include "../ft_ls.h"

void	main_twelve(int argc, char **argv, t_lists *lists)
{
	/*
	** -Rral
	*/
	if (lists->rflag > 0 && lists->tflag == 0 && \
		lists->big_r_flag > 0 && lists->lflag > 0 && \
		lists->aflag > 0)
	{
		if (argc == 2)
		{
		    argv[2] = ".";
		    argc = 3;
		}
		lists->i = 0;
		Rrl_helper(argv[2], 1, lists);
		list_dirbigrrl(argv[2], 1, lists);
		exit(0);
	}
	/*
	** -Rrlt
	*/
	else if (lists->rflag > 0 && lists->tflag > 0 && \
		lists->big_r_flag > 0 && lists->lflag > 0 && \
		lists->aflag == 0)		
	{
		if (argc == 2)
		{
		    argv[2] = ".";
		    argc = 3;
		}
		lists->i = 0;
		everything_helper(argv[2], 0, lists);
		everything(argv[2], 0, lists);
		exit(0);
	}
}

void	main_thirteen(int argc, char **argv, t_lists *lists)
{
	/*
	** -Rrta
	*/
	if (lists->rflag > 0 && lists->tflag > 0 && \
		lists->big_r_flag > 0 && lists->lflag == 0 && \
		lists->aflag > 0)			
	{
		if (argc == 2)
		{
		    argv[2] = ".";
		    argc = 3;
		}
		lists->i = 0;
		rbigrt_helper(argv[2], 1, lists);
		rbigrt(argv[2], 1, lists);
		exit(0);
	}
	/*
	** -Rlta
	*/
	if (lists->rflag == 0 && lists->tflag > 0 && \
		lists->big_r_flag > 0 && lists->lflag > 0 && \
		lists->aflag > 0)				
	{
		if (argc == 2)
		{
		    argv[2] = ".";
		    argc = 3;
		}
		lists->i = 0;
		rlt_helper(argv[2], 1, lists);
		rlt(argv[2], 1, lists);
		exit(0);
	}
}

void	main_fourteen(int argc, char **argv, t_lists *lists)
{
	/*
	** - Rrlta
	*/
	if (lists->rflag > 0 && lists->tflag > 0 && \
		lists->big_r_flag > 0 && lists->lflag > 0 && \
		lists->aflag > 0)		
	{
		if (argc == 2)
		{
		    argv[2] = ".";
		    argc = 3;
		}
		lists->i = 0;
		everything_helper(argv[2], 1, lists);
		everything(argv[2], 1, lists);
		exit(0);
	}
}