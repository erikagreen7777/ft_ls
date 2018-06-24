#include "../ft_ls.h"

void		init_struct(t_lists **lists)
{
	*lists = (t_lists *)ft_memalloc(sizeof(t_lists));
	(*lists)->timearray = NULL;
	(*lists)->filecount = 0;
	(*lists)->dest = NULL;
	(*lists)->temp = NULL;
	(*lists)->tempdest = NULL;
	(*lists)->tflag = 0;
	(*lists)->big_r_flag = 0;
	(*lists)->rflag = 0;
	(*lists)->lflag = 0;
	(*lists)->aflag = 0;

}

// static void	free_stuff(t_lists **lists)
// {
// 	// ft_memdel((void*)&lists->timearray);
// 	// ft_memdel((void*)&lists->dest);
// 	ft_memdel((void*)&lists);
// }

int main(int argc, char **argv)
{
	if (ft_strcmp(argv[0], "./ft_ls") == 0)
	{
		t_lists *lists;
		lists = NULL;
		/*
		** ls with no args
		*/
		if (argc == 1 || (argc == 2 && ft_strcmp(argv[1], ".") == 0))
		{
			list_dir(argc, argv);
			return (0);
		}
		if (argc >= 2)
		{

			init_struct(&lists);

			arg_parsing(argc, argv, lists);
			/*
			** -r
			*/
			if (lists->rflag > 0 && lists->tflag == 0 && \
				lists->big_r_flag == 0 && lists->lflag == 0 && \
				lists->aflag == 0)
				{
					init_struct(&lists);
					list_dirr(argc, argv, lists);
					return (0);
				}
			/*
			** -t
			*/
			if (lists->rflag == 0 && lists->tflag > 0 && \
				lists->big_r_flag == 0 && lists->lflag == 0 && \
				lists->aflag == 0)		
			{
				init_struct(&lists);
				list_dirt(argc, argv, lists);
			}
			/*
			** -a
			*/
			if (lists->rflag == 0 && lists->tflag == 0 && \
				lists->big_r_flag == 0 && lists->lflag == 0 && \
				lists->aflag > 0)				
				list_dira(argc, argv);
			/*
			** -l
			*/
			if (lists->rflag == 0 && lists->tflag == 0 && \
				lists->big_r_flag == 0 && lists->lflag > 0 && \
				lists->aflag == 0)		
			{
				init_struct(&lists);
				list_dirl(argc, argv, lists);
			}
			/*
			** -R
			*/
			if (lists->rflag == 0 && lists->tflag == 0 && \
				lists->big_r_flag > 0 && lists->lflag == 0 && \
				lists->aflag == 0)	
			{
				if (argc == 2)
				{
				    argv[2] = ".";
				    argc = 3;
				}
				init_struct(&lists);
				lists->i = 0;
				R_first(argc, argv, 0);
				list_dirbigr(argv[2], 0);
			}
			/*
			** -la
			*/
			if (lists->rflag == 0 && lists->tflag == 0 && \
				lists->big_r_flag == 0 && lists->lflag > 0 && \
				lists->aflag > 0)			
			{
				init_struct(&lists);
				ls_la(argc, argv, lists);
				return (0);
			}
			/*
			** -at
			*/
			if (lists->rflag == 0 && lists->tflag > 0 && \
				lists->big_r_flag == 0 && lists->lflag == 0 && \
				lists->aflag > 0)	
			{
				init_struct(&lists);
				list_dirta(argc, argv, lists);
				return (0);
			}
			/*
			** -tl
			*/
			if (lists->rflag == 0 && lists->tflag > 0 && \
				lists->big_r_flag == 0 && lists->lflag > 0 && \
				lists->aflag == 0)	
			{
				init_struct(&lists);
				ls_lt(argc, argv, lists);
				return (0);
			}
			/*
			** -ra
			*/
			if (lists->rflag > 0 && lists->tflag == 0 && \
				lists->big_r_flag == 0 && lists->lflag == 0 && \
				lists->aflag > 0)	
			{
				init_struct(&lists);
				ls_ra(argc, argv, lists);
				return (0);
			}	
			/*
			** -rt
			*/
			if (lists->rflag > 0 && lists->tflag > 0 && \
				lists->big_r_flag == 0 && lists->lflag == 0 && \
				lists->aflag == 0)	
			{
				init_struct(&lists);
				ls_rt(argc, argv, lists);
				return (0);
			}
			/*
			** -rl
			*/
			if (lists->rflag > 0 && lists->tflag == 0 && \
				lists->big_r_flag == 0 && lists->lflag > 0 && \
				lists->aflag == 0)			
			{
				init_struct(&lists);
				list_dirlr(argc, argv, lists);
				return (0);
			}
			/*
			** -Ra
			*/
			if (lists->rflag == 0 && lists->tflag == 0 && \
				lists->big_r_flag > 0 && lists->lflag == 0 && \
				lists->aflag > 0)	
			{
				if (argc == 2)
				{
				    argv[2] = ".";
				    argc = 3;
				}
				init_struct(&lists);
				lists->i = 0;
				R_first(argc, argv, 1);
				list_dirbigr(argv[2], 1);
				return (0);
			}
			/*
			** -Rt
			*/
			if (lists->rflag == 0 && lists->tflag > 0 && \
				lists->big_r_flag > 0 && lists->lflag == 0 && \
				lists->aflag == 0)		
			{
				if (argc == 2)
				{
				    argv[2] = ".";
				    argc = 3;
				}
				init_struct(&lists);
				lists->i = 0;
				Rt_helper(argv[2], 0, lists);
				list_dirbigrt(argv[2], 0, lists);
				return (0);
			}
			/*
			** -Rr
			*/
			if (lists->rflag > 0 && lists->tflag == 0 && \
				lists->big_r_flag > 0 && lists->lflag == 0 && \
				lists->aflag == 0)			
			{
				if (argc == 2)
				{
				    argv[2] = ".";
				    argc = 3;
				}
				init_struct(&lists);
				lists->i = 0;
				Rr_helper(argv[2], 0, lists);
				list_dirbigrr(argv[2], 0, lists);
				return (0);
			}
			/*
			** -Rl
			*/
			if (lists->rflag == 0 && lists->tflag == 0 && \
				lists->big_r_flag > 0 && lists->lflag > 0 && \
				lists->aflag == 0)			
			{
				if (argc == 2)
				{
				    argv[2] = ".";
				    argc = 3;
				}
				init_struct(&lists);
				lists->i = 0;
				Rl_helper(argv[2], 0, lists);
				list_dirbigrl(argv[2], 0, lists);
				return (0);
			}
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
				init_struct(&lists);
				lists->i = 0;
				Rl_helper(argv[2], 1, lists);
				list_dirbigrl(argv[2], 1, lists);
				return (0);
			}
			/*
			** - rlt
			*/
			if (lists->rflag > 0 && lists->tflag > 0 && \
				lists->big_r_flag == 0 && lists->lflag > 0 && \
				lists->aflag == 0)			
			{
				init_struct(&lists);
				ls_lrt(argc, argv, lists);
				return (0);
			}
			/*
			** -rat
			*/
			if (lists->rflag > 0 && lists->tflag > 0 && \
				lists->big_r_flag == 0 && lists->lflag == 0 && \
				lists->aflag > 0)	
			{	
				init_struct(&lists);
				ls_rat(argc, argv, lists);
				return (0);
			}
			/*
			** - rla
			*/
			if (lists->rflag > 0 && lists->tflag == 0 && \
				lists->big_r_flag == 0 && lists->lflag > 0 && \
				lists->aflag > 0)		
			{
				init_struct(&lists);
				ls_lra(argc, argv, lists);
				return (0);
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
				init_struct(&lists);
				lists->i = 0;
				rbigrt_helper(argv[2], 0, lists);
				rbigrt(argv[2], 0, lists);
				return (0);
			}
			/*
			** -tal
			*/
			if (lists->rflag == 0 && lists->tflag > 0 && \
				lists->big_r_flag == 0 && lists->lflag > 0 && \
				lists->aflag > 0)	
			{
				init_struct(&lists);
				ls_lta(argc, argv, lists);
				return (0);
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
				init_struct(&lists);
				lists->i = 0;
				Rt_helper(argv[2], 1, lists);
				list_dirbigrt(argv[2], 1, lists);
				return (0);
			}
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
				init_struct(&lists);
				lists->i = 0;
				rlt_helper(argv[2], 0, lists);
				rlt(argv[2], 0, lists);
				return (0);
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
				init_struct(&lists);
				lists->i = 0;
				Rr_helper(argv[2], 1, lists);
				list_dirbigrr(argv[2], 1, lists);
				return (0);
			}
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
				init_struct(&lists);
				lists->i = 0;
				Rrl_helper(argv[2], 0, lists);
				list_dirbigrrl(argv[2], 0, lists);
				return (0);
			}
			/*
			** -lrat
			*/
			if (lists->rflag > 0 && lists->tflag > 0 && \
				lists->big_r_flag == 0 && lists->lflag > 0 && \
				lists->aflag > 0)
			{
				init_struct(&lists);
				ls_lrat(argc, argv, lists);
				return (0);
			}
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
				init_struct(&lists);
				lists->i = 0;
				Rrl_helper(argv[2], 1, lists);
				list_dirbigrrl(argv[2], 1, lists);
				return (0);
			}
			/*
			** -Rrlt
			*/
			if (lists->rflag > 0 && lists->tflag > 0 && \
				lists->big_r_flag > 0 && lists->lflag > 0 && \
				lists->aflag == 0)		
			{
				if (argc == 2)
				{
				    argv[2] = ".";
				    argc = 3;
				}
				init_struct(&lists);
				lists->i = 0;
				everything_helper(argv[2], 0, lists);
				everything(argv[2], 0, lists);
				return (0);
			}
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
				init_struct(&lists);
				lists->i = 0;
				rbigrt_helper(argv[2], 1, lists);
				rbigrt(argv[2], 1, lists);
				return (0);
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
				init_struct(&lists);
				lists->i = 0;
				rlt_helper(argv[2], 1, lists);
				rlt(argv[2], 1, lists);
				return (0);
			}
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
				init_struct(&lists);
				lists->i = 0;
				everything_helper(argv[2], 1, lists);
				everything(argv[2], 1, lists);
				return (0);
			}
			/* 
			** ls
			*/
			else
				list_dir(argc, argv);
		}
		else
			ft_error("main: ./ft_ls error");
	}
	return (0);
}