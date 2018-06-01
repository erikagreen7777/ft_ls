#include "../ft_ls.h"

void	list_dirl(int argc, char **argv)
{
	int				j;
	DIR				*dip;
	struct dirent	*dit;
	char			**splitstr;
	int				i;
	int				linecount;
	linecount = 0;
	i = 0;
	j = 2;
	splitstr = NULL;
	while (j < argc)
	{
		if (ls_stat(argv[j]) != 0)
		{
			dip = opendir(argv[j]);
			if (dip == NULL)
			{
				ft_error(": No file or directory");
			}
			while ((dit = readdir(dip)) != NULL)
			{
				printf("hello!\n");
				if (dit->d_name[0] != '.')
				{
					splitstr[i] = ft_strdup(dit->d_name);
					i++;
					printf("i: %d\n", i);
					ft_printf("here: %s\n", dit->d_name);
				}
			}
			if (closedir(dip) == -1)
				ft_error("closedir");
		}
		j++;
	}
	linecount = i;
	printf("linecount: %d\n", linecount);
	i = 0;
	while (splitstr[i] != NULL)
	{
		printf("splitstr: %s\n", splitstr[i]);
		i++;
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
