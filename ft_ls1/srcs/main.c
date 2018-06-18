#include "../ft_ls.h"

void		init_struct(t_lists **lists)
{
	*lists = (t_lists *)ft_memalloc(sizeof(t_lists));
	(*lists)->timearray = NULL;
	(*lists)->filecount = 0;
	(*lists)->dest = NULL;
	(*lists)->temp = NULL;
	(*lists)->tempdest = NULL;

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
			/*
			** -la
			*/
			if ((ft_strcmp(argv[1], "-la") == 0) || (ft_strcmp(argv[1], "-al") == 0))
			{
				init_struct(&lists);
				ls_la(argc, argv, lists);
				return (0);
			}
			/*
			** -lrat
			*/
			else if ((ft_strcmp(argv[1], "-lrat") == 0) || ft_strcmp(argv[1], "-lrta") == 0 || \
				(ft_strcmp(argv[1], "-lart") == 0) || ft_strcmp(argv[1], "-latr") == 0 || \
				ft_strcmp(argv[1], "-ltra") == 0 || ft_strcmp(argv[1], "-ltar") == 0 || \
				ft_strcmp(argv[1], "-rlat") == 0 || ft_strcmp(argv[1], "-rlta") == 0 || \
				ft_strcmp(argv[1], "-ralt") == 0 || ft_strcmp(argv[1], "-ratl") == 0 || \
				ft_strcmp(argv[1], "-rtla") == 0 || ft_strcmp(argv[1], "-rtal") == 0 || \
				ft_strcmp(argv[1], "-alrt") == 0 || ft_strcmp(argv[1], "-altr") == 0 || \
				ft_strcmp(argv[1], "-arlt") == 0 || ft_strcmp(argv[1], "-artl") == 0 || \
				ft_strcmp(argv[1], "-atlr") == 0 || ft_strcmp(argv[1], "-atrl") == 0 || \
				ft_strcmp(argv[1], "-tlra") == 0 || ft_strcmp(argv[1], "-tlar") == 0 || \
				ft_strcmp(argv[1], "-trla") == 0 || ft_strcmp(argv[1], "-tral") == 0 || \
				ft_strcmp(argv[1], "-talr") == 0 || ft_strcmp(argv[1], "-tarl") == 0)
			{
				init_struct(&lists);
				ls_lrat(argc, argv, lists);
				return (0);
			}
			/*
			** -tl
			*/
			else if ((ft_strcmp(argv[1], "-tl") == 0) || ft_strcmp(argv[1], "-lt") == 0)
			{
				init_struct(&lists);
				ls_lt(argc, argv, lists);
				return (0);
			}
			/*
			** -ra
			*/
			else if ((ft_strcmp(argv[1], "-ra") == 0) || ft_strcmp(argv[1], "-ar") == 0)
			{
				init_struct(&lists);
				ls_ra(argc, argv, lists);
				return (0);
			}
			/*
			** -rat
			*/
			else if ((ft_strcmp(argv[1], "-rat") == 0) || ft_strcmp(argv[1], "-rta") == 0 || \
				(ft_strcmp(argv[1], "-art") == 0) || ft_strcmp(argv[1], "-atr") == 0 || \
				ft_strcmp(argv[1], "-tra") == 0 || ft_strcmp(argv[1], "-tar") == 0)
			{	
				init_struct(&lists);
				ls_rat(argc, argv, lists);
				return (0);
			}
			/*
			** -rt
			*/
			else if ((ft_strcmp(argv[1], "-rt") == 0) || ft_strcmp(argv[1], "-tr") == 0)
			{
				init_struct(&lists);
				ls_rt(argc, argv, lists);
				return (0);
			}
			/*
			** -tal
			*/
			else if ((ft_strcmp(argv[1], "-tal") == 0) || ft_strcmp(argv[1], "-lta") == 0 || \
				(ft_strcmp(argv[1], "-lat") == 0) || ft_strcmp(argv[1], "-tla") == 0 || \
				ft_strcmp(argv[1], "-alt") == 0 || ft_strcmp(argv[1], "-atl") == 0)
			{
				init_struct(&lists);
				ls_lta(argc, argv, lists);
				return (0);
			}
			/*
			** -a
			*/
			else if (ft_strcmp(argv[1], "-a") == 0)
				list_dira(argc, argv);
			/*
			** -l
			*/
			else if (ft_strcmp(argv[1], "-l") == 0)
			{
				init_struct(&lists);
				list_dirl(argc, argv, lists);
			}
			/*
			** -r
			*/
			else if (ft_strcmp(argv[1], "-r") == 0)
			{
				init_struct(&lists);
				list_dirr(argc, argv, lists);
				return (0);
			}
			/*
			** -R
			*/
			else if (ft_strcmp(argv[1], "-R") == 0)
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
			** -Ra
			*/
			else if ((ft_strcmp(argv[1], "-Ra") == 0) || ft_strcmp(argv[1], "-aR") == 0)
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
			else if ((ft_strcmp(argv[1], "-Rt") == 0) || ft_strcmp(argv[1], "-tR") == 0)
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
			** -Rta
			*/
			else if (ft_strcmp(argv[1], "-Rta") == 0 || ft_strcmp(argv[1], "-atR") == 0 || \
				ft_strcmp(argv[1], "-Rat") == 0 || ft_strcmp(argv[1], "-tRa") == 0 || \
				ft_strcmp(argv[1], "-taR") == 0 || ft_strcmp(argv[1], "-aRt") == 0)

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
			** -Rl
			*/
			else if ((ft_strcmp(argv[1], "-Rl") == 0) || ft_strcmp(argv[1], "-lR") == 0)
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
			else if (ft_strcmp(argv[1], "-Rla") == 0 || ft_strcmp(argv[1], "-alR") == 0 || \
				ft_strcmp(argv[1], "-Ral") == 0 || ft_strcmp(argv[1], "-lRa") == 0 || \
				ft_strcmp(argv[1], "-laR") == 0 || ft_strcmp(argv[1], "-aRl") == 0)			{
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
			** -Rr
			*/
			else if ((ft_strcmp(argv[1], "-Rr") == 0) || ft_strcmp(argv[1], "-rR") == 0)
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
			** -t
			*/
			else if (ft_strcmp(argv[1], "-t") == 0)
			{
				init_struct(&lists);
				list_dirt(argc, argv, lists);
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