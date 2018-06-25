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
			everything(argv[j], 0, lists);
		}
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