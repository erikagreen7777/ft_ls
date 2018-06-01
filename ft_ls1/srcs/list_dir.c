#include "../ft_ls.h"

void	list_dirl(int argc, char **argv)
{
	// DIR				*dip;
	// struct dirent	*dit;
	// struct stat 	fileStat;
	int				j;
	// char			*str;
	j = 2;
	// char			**str;

	printf("argc: %d\targv[2]: %s\n", argc, argv[2]);

	while (j < argc)
	{
		ls_stat(argv[j]);
	// 	if (j > 2 && j < argc)
	// 		write(1, "\n", 1);
	// 	dip = opendir(argv[j]);
	// 	if (dip == NULL)
	// 	{
 //        	ls_stat(argv[j]);
	// 		exit(1);
	// 	}
	// 	while ((dit = readdir(dip)) != NULL)
	// 	{
	// 		if (dit->d_name[0] != '.')
	// 			ls_stat(dit->d_name);
	// 			ft_printf("here: %s\n", dit->d_name);
	// 	}
	// 	if (closedir(dip) == -1)
	// 		ft_error("closedir");
		j++;
	}
}

void	list_dir(int argc, char **argv)
{
	DIR				*dip;
	struct dirent	*dit;
	struct stat 	fileStat;
	int				j;
	j = 1;
	while (j < argc)
	{
		if (j > 1 && j < argc)
			write(1, "\n", 1);
		dip = opendir(argv[j]);
		if (dip == NULL)
		{
				if(stat(argv[j],&fileStat) < 0)  
        			ft_error(": No such file or directory");
				printf("%s\n", argv[j]);
				exit(1);
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

void	list_dira(int argc, char **argv)
{
	DIR				*dip;
	struct dirent	*dit;
	struct stat 	fileStat;
	int				j;
	j = 2;
	while (j < argc)
	{
		if (j > 2 && j < argc)
			write(1, "\n", 1);
		dip = opendir(argv[j]);
		if (dip == NULL)
		{
				if(stat(argv[j],&fileStat) < 0)  
        			ft_error(": No such file or directory");
				printf("%s\n", argv[j]);
				exit(1);
		}
		while ((dit = readdir(dip)) != NULL)
			ft_printf("%s\n", dit->d_name);
		if (closedir(dip) == -1)
			ft_error("closedir");
		j++;
	}
}

static void	lex_sort(DIR *dip)
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
	while (--filecount > -1)
		printf("%s\n", str[filecount]);
}

void	list_dirr(int argc, char **argv)
{
	DIR				*dip;
	struct stat 	fileStat;
	int				j;
	j = 2;
	while (j < argc)
	{
		if (j > 2 && j < argc)
			write(1, "\n", 1);
		dip = opendir(argv[j]);
		if (dip == NULL)
		{
				if(stat(argv[j],&fileStat) < 0)  
        			ft_error(": No such file or directory");
				printf("%s\n", argv[j]);
				exit(1);
		}
		lex_sort(dip);
		if (closedir(dip) == -1)
			ft_error("closedir");
		j++;
	}
}


  //      	//just printing out the file name
   //      	//not going to work for the stat function
   //      	//separate the argv by / and open from there. 
			// printf("%s\n", argv[j]);
			// str = extract_path(argv[j]);
			// if(stat(argv[j],&fileStat) < 0)  
   //      		ft_error(": No such file or directory");
