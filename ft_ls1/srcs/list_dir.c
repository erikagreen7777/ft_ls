#include "../ft_ls.h"

void	lex_sort(DIR *dip)
{
	int		filecount;
	int		i;
	int		j;
	struct dirent *dit;
	char	tmp[D_NAME_MAX][WORD_MAX];
	filecount = 0;
	i = 0;
	j = 0;

	while ((dit = readdir(dip)) != NULL)
	{
		if (dit->d_name[0] != '.')
		{
			ft_strcpy(tmp[i], dit->d_name);
			filecount++;
			i++;
		}
	}
	i = 0;
	// dip = opendir(argv[j]);
	while (i < filecount)
	{
		printf("temp[i]: %s[%d]\n", tmp[i], i);
		i++;
	}
	// if (closedir(dip) == -1)
	// 	ft_error("closedir");
	printf("filecount: %d\n", filecount);

	// while ((dit = readdir(dip)) != NULL)
	// {
	// 	if (dit->d_name[0] != '.')
	// 	{
	// 		// if (ft_strcmp(dit->d_name) > dit->d_name)
	// 		ft_printf("%s\n", dit->d_name[0]);			
	// 		i++;
	// 	}
	// }
	// exit(0);
	// while (dit->d_name[i])
	// {
	// 	while (dit->d_name[i][j])
	// 	{
	// 		if(ft_strcmp(str[i], str[j])>0)
	//             {
	//                 ft_strcpy(temp, str[i]);
	//                 ft_strcpy(str[i], str[j]);
	//                 ft_strcpy(str[j], temp);
	//             }
	// 		j++;
	// 	}
	// 	i++;
	// }
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
	// struct dirent	*dit;
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
		// dip = opendir(argv[j]);
		// while ((dit = readdir(dip)) != NULL)
		// {
		// 	if (dit->d_name[0] != '.')
		// 		ft_printf("%s\n", dit->d_name);
		// 	i++;
		// }
		if (closedir(dip) == -1)
			ft_error("closedir");
		j++;
	}
}