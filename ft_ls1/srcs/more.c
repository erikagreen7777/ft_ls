#include "../ft_ls.h"

void	ls_ra(int argc, char **argv, t_lists *lists)
{
	DIR				*dip;
	struct stat 	fileStat;
	char 			**array;
	struct dirent	*dit;
	char			arg[WORD_MAX];
	char  			temp[WORD_MAX];
	int				j;
	j = 1;
	
	if (argc == 2)
	{
		argv[j + 1] = ".";
		argc = 3;
	}
	while (++j < argc)
	{
		if (j > 2 && j < argc)
			write(1, "\n", 1);
		dip = opendir(argv[j]);
		if (dip == NULL)
		{
				if(stat(argv[j],&fileStat) < 0)  
        			ft_error("ls -r: No such file or directory");
				printf("%s\n", argv[j]);
				exit(1);
		}
		if (closedir(dip) == -1)
			ft_error("closedir");
		lists->filecount = directory_count(dip, argv[j], 1);
		dip = opendir(argv[j]);
		lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
		array = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
		if (dip == NULL)
		{
			ft_error(": No file or directory");
		}
		ft_strcpy(temp, arg);
		while ((dit = readdir(dip)) != NULL)
		{
			if (lists->i > 0)
				ft_strcpy(arg, temp);
			ft_strcat(arg, dit->d_name);
			lists->dest[lists->i] = ft_strdup(arg);
			ft_bzero(arg, ft_strlen(arg));
			lists->i++;
		}
		if (closedir(dip) == -1)
			ft_error("closedir");
		lex_sort(lists);
	}
}