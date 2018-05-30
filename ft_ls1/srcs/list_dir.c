#include "../ft_ls.h"

void	lex_sort(DIR *dip)
{
	int		filecount;
	int		i;
	struct 	dirent *dit;
	char	str[D_NAME_MAX][WORD_MAX];
	filecount = 0;
	i = 0;

	while ((dit = readdir(dip)) != NULL)
	{
		if (dit->d_name[0] != '.')
		{
			ft_strcpy(str[i], dit->d_name);
			filecount++;
			i++;
		}
	}
	//print out strcopy of dirent
	while (--filecount > -1)
	{
		printf("%s\n", str[filecount]);
		// filecount--;
	}
}

void	list_dir(int argc, char **argv)
{
	DIR				*dip;
	struct dirent	*dit;
	struct stat 	fileStat;
	int 			i;
	int				j;
	i = 0;
	j = 1;
	while (j < argc)
	{
		if (j > 1 && j < argc)
			write(1, "\n", 1);
		dip = opendir(argv[j]);
		if (dip == NULL)
		{
				if(stat(argv[j],&fileStat) < 0) 
        			ft_error("stat error");
				printf("%s\n", argv[j]);
				exit(1);
		}
		while ((dit = readdir(dip)) != NULL)
		{
			if (dit->d_name[0] != '.')
				ft_printf("%s\n", dit->d_name);
			i++;
		}
		if (closedir(dip) == -1)
			ft_error("closedir");
		j++;
	}
}

void	list_dira(int argc, char **argv)
{
	DIR				*dip;
	struct dirent	*dit;
	struct stat 	fileStat;
	int 			i;
	int				j;
	i = 0;
	j = 2;
	while (j < argc)
	{
		if (j > 2 && j < argc)
			write(1, "\n", 1);
		dip = opendir(argv[j]);
		if (dip == NULL)
		{
				if(stat(argv[j],&fileStat) < 0)  
        			ft_error("stat error");
				printf("%s\n", argv[j]);
				exit(1);
		}
		while ((dit = readdir(dip)) != NULL)
		{
			ft_printf("%s\n", dit->d_name);
			i++;
		}
		if (closedir(dip) == -1)
			ft_error("closedir");
		j++;
	}
}

void	list_dirr(int argc, char **argv)
{
	DIR				*dip;
	struct stat 	fileStat;
	int 			i;
	int				j;
	i = 0;
	j = 2;
	while (j < argc)
	{
		if (j > 2 && j < argc)
			write(1, "\n", 1);
		dip = opendir(argv[j]);
		if (dip == NULL)
		{
				if(stat(argv[j],&fileStat) < 0)  
        			ft_error("stat error");
				printf("%s\n", argv[j]);
				exit(1);
		}
		lex_sort(dip);
		if (closedir(dip) == -1)
			ft_error("closedir");
		j++;
	}
}