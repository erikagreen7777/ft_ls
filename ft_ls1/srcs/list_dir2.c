#include "../ft_ls.h"

/*
** ls 
*/
void	list_dir(int argc, char **argv)
{
	DIR				*dip;
	struct dirent	*dit;
	struct stat 	fileStat;
	int				j;
	j = 1;
	if (argc == 1)
	{
		argv[j] = ".";
		argc = 2;
	}
	while (j < argc)
	{
		if (j > 1 && j < argc)
			write(1, "\n", 1);
		dip = opendir(argv[j]);
		if (dip == NULL)
		{
			/*
			** TODO: create own function for this because it happens often?
			*/
	
				if(stat(argv[j],&fileStat) < 0) 
				{
					ft_printf("./ft_ls: %s: No such file or directory\n", argv[j]);
					exit (-1);
				} 
				printf("%s\n", argv[j]);
				exit(0);
			/*
			** end function here?
			*/
		}
		while ((dit = readdir(dip)) != NULL)
		{
			if (dit->d_name[0] != '.')
				ft_printf("%s\n", dit->d_name);
		}
		if (closedir(dip) == -1)
			ft_error("closedir");
		j++;
	}
}

/*
** ls -a
*/
void	list_dira(int argc, char **argv, t_lists *lists)
{
	DIR				*dip;
	struct dirent	*dit;
	lists->j = 1;

	if (argc == 2)
	{
		argv[2] = ".";
		argc = 3;
	}
	while (++lists->j < argc)
	{
		if (lists->j > 2 && lists->j < argc)
			write(1, "\n", 1);
		dip = opendir(argv[lists->j]);
		if (dip == NULL)
			null_check(argv[lists->j]);
		while ((dit = readdir(dip)) != NULL)
			ft_printf("%s\n", dit->d_name);
		if (closedir(dip) == -1)
			ft_error("closedir");
	}
}
