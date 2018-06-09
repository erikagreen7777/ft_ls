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
			if (ft_strcmp(argv[1], "-a") == 0)
			{
				
				// if (argc < 3)
				// 	ft_error("Usage: ./ft_ls -a <directory>");
				list_dira(argc, argv);
			}
			else if (ft_strcmp(argv[1], "-l") == 0)
			{
				// if (argc < 3)
				// 	ft_error("Usage: ./ft_ls -l <directory>");
				init_struct(&lists);
				list_dirl(argc, argv, lists);
				/*
				** TODO: free stuff?
				*/
				// free_stuff(&lists);

			}
			else if (ft_strcmp(argv[1], "-r") == 0)
			{
				// if (argc < 3)
				// 	ft_error("Usage: ./ft_ls -r <directory>");
				list_dirr(argc, argv, lists);
			}
			else if (ft_strcmp(argv[1], "-R") == 0)
			{
				if (argc == 2)
				{
				    argv[2] = ".";
				    argc = 3;
				}
				// if (argc < 3)
				// 	ft_error("Usage: ./ft_ls -R <directory>");
				list_dirbigr(argv[2]);
			}
			else if (ft_strcmp(argv[1], "-t") == 0)
			{
				init_struct(&lists);
				list_dirt(argc, argv, lists);
				/*
				** TODO: free stuff?
				** free_stuff(&lists);
				*/
				// free_stuff(&lists);
			}
			else
				list_dir(argc, argv);
		}
		
		else
			ft_error("main: ./ft_ls error");
	}
	return (0);
}