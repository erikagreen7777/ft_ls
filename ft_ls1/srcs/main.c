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
		if (argc == 1 || (argc == 2 && ft_strcmp(argv[1], ".") == 0))
		{
			list_dir(argc, argv);
			return (0);
		}
		if (argc >= 2)
		{
			if ((ft_strcmp(argv[1], "-la") == 0) || (ft_strcmp(argv[1], "-al") == 0))
			{
				init_struct(&lists);
				ls_la(argc, argv, lists);
				return (0);
			}			
			else if ((ft_strcmp(argv[1], "-tl") == 0) || ft_strcmp(argv[1], "-lt") == 0)
			{
				init_struct(&lists);
				ls_lt(argc, argv, lists);
				return (0);
			}
			else if ((ft_strcmp(argv[1], "-ra") == 0) || ft_strcmp(argv[1], "-ar") == 0)
			{
				init_struct(&lists);
				ls_ra(argc, argv, lists);
				return (0);
			}
			else if ((ft_strcmp(argv[1], "-tal") == 0) || ft_strcmp(argv[1], "-lta") == 0 || \
				(ft_strcmp(argv[1], "-lat") == 0) || ft_strcmp(argv[1], "-tla") == 0 || \
				ft_strcmp(argv[1], "-alt") == 0 || ft_strcmp(argv[1], "-atl") == 0)
			{
				init_struct(&lists);
				ls_lta(argc, argv, lists);
				return (0);
			}
			else if (ft_strcmp(argv[1], "-a") == 0)
			{				
				list_dira(argc, argv);
			}
			else if (ft_strcmp(argv[1], "-l") == 0)
			{
				init_struct(&lists);
				list_dirl(argc, argv, lists);
			}
			else if (ft_strcmp(argv[1], "-r") == 0)
			{
				init_struct(&lists);
				list_dirr(argc, argv, lists);
			}
			else if (ft_strcmp(argv[1], "-R") == 0)
			{
				if (argc == 2)
				{
				    argv[2] = ".";
				    argc = 3;
				}
				init_struct(&lists);
				lists->i = 0;
				R_first(argc, argv);
				list_dirbigr(argv[2]);
			}
			else if (ft_strcmp(argv[1], "-t") == 0)
			{
				init_struct(&lists);
				list_dirt(argc, argv, lists);
			}
			else
				list_dir(argc, argv);
		}
		
		else
			ft_error("main: ./ft_ls error");
	}
	return (0);
}