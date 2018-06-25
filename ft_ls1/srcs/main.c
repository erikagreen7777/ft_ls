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
	(*lists)->k = 0;
	(*lists)->i = 0;
	(*lists)->j = 0;
	(*lists)->newargc = 0;
	(*lists)->firstarg = 0;
	(*lists)->timearrayflag = 0;
	(*lists)->itoatemp = NULL;

}

void	free_struct(t_lists *lists)
{
	int i;
	i = 0;
	while (i < lists->filecount)
	{
		if (lists->timearrayflag > 0)
			free(lists->timearray[i]);
		free(lists->dest[i]);
		i++;
	}
	if (lists->timearrayflag > 0)
	{
		free(lists->itoatemp);
		free(lists->timearray);
	}
	ft_memdel((void*)&lists->timearray);
	ft_memdel((void*)&lists->dest);
	free(lists->dest);
	free(lists);
}

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
			// return (0);
		}
		else if (argc >= 2)
		{
			init_struct(&lists);
			lists->newargc = arg_parsing(argc, argv, lists);
			the_start(argc, argv, lists);
			list_dir(argc, argv);
			free_struct(lists);
		}
		else
			ft_error("main: ./ft_ls error");
	}
	return (0);
}
