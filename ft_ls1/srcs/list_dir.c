#include "../ft_ls.h"

/*
** helper function for ls -t
*/
static int		directory_count(DIR *dip, char *str)
{
	int		filecount;
	struct 	dirent *dit;
	filecount = 0;
	// str = NULL;

	while ((dit = readdir(dip)) != NULL)
	{
		if (dit->d_name[0] != '.')
		{
			filecount++;
		}
	}
	if (closedir(dip) == -1)
		ft_error("closedir");

	dip = opendir(str);
	return (filecount);
}


/*
** ls -l
*/
void	list_dirl(int argc, char **argv, t_lists *lists)
{
	int				j;
	DIR				*dip;
	struct dirent	*dit;
	char			splitstr[1000];
	int				i;
	struct stat 	fileStat;
	int				filecount;
	// char			dest[257][10000];
	char			*arg;
	int 			size;

	size = 0;
	i = 0;
	j = 2;
	arg = (char *)malloc(sizeof(ft_strlen(argv[j]) + 1));
	if (argc == 2)
	{
		argv[j] = ".";
		argc = 3;
	}
	while (j < argc)
	{

		if(stat(argv[j], &fileStat) < 0) 
        	ft_error(": No such file or directory");

		if ((fileStat.st_mode & S_IFMT) == S_IFREG)
			ls_stat(argv[j]);
		else if (S_ISDIR(fileStat.st_mode) == 1)
		{
			dip = opendir(argv[j]);
			ft_strcpy(arg, argv[j]);
			/*
			** if the last character isn't a /, then attach a slash to the end of the arg
			*/
			if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
				ft_strcat(arg, "/");
			if (dip == NULL)
			{
				ft_error(": No file or directory");
			}
			while ((dit = readdir(dip)) != NULL)
			{
				if (dit->d_name[0] != '.')
				{	
					ft_strcpy(lists->dest[i], arg);
					// splitstr = (char *)malloc(sizeof(ft_strlen(dit->d_name)));
					ft_strcpy(splitstr, dit->d_name);
					ft_strcat(lists->dest[i], splitstr);
					ft_bzero(splitstr, ft_strlen(splitstr));
					// free(splitstr);
					i++;
				}
			}
			if (closedir(dip) == -1)
				ft_error("closedir");
		}
		j++;
	}
	filecount = i;
	i = -1;
	while (++i < filecount)
		size += add_stat(lists->dest[i]);
	ft_printf("total %d\n", size);
	i = -1;
	while (++i < filecount)
		ls_stat(lists->dest[i]);
	free(dip);
	free(arg);

}


/*
** ls -t
*/
void	list_dirt(int argc, char **argv, t_lists *lists)
{
	int				j;
	DIR				*dip;
	struct dirent	*dit;
	char			**splitstr;
	int				i;
	struct stat 	fileStat;
	char			arg[WORD_MAX];
	i = 0;
	j = 2;
	if (argc == 2)
	{
		argv[j] = ".";
		argc = 3;
	}
	while (j < argc)
	{
		/*
		** if the file/folder isn't valid
		*/
		if(stat(argv[j], &fileStat) < 0) 
        	ft_error(": No such file or directory");
    	/*
    	** if it's a regular file
		*/
		if ((fileStat.st_mode & S_IFMT) == S_IFREG)
			ls_stat(argv[j]);
		else if (S_ISDIR(fileStat.st_mode) == 1)
		{
			dip = opendir(argv[j]);
			ft_strcpy(arg, argv[j]);
	        /*
	        ** if the last character of argv[j] isn't a "/", add one
	        */
			if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
				ft_strcat(arg, "/");
			lists->filecount = directory_count(dip, argv[j]);
			/*
			** malloc memory for the 2D array (include extra + 1 for null at end)
			*/
			splitstr = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
			lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
			lists->timearray = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
			if (dip == NULL)
			{
				ft_error(": No file or directory");
			}
			/*
			** TODO: end split function here?
			*/
			while ((dit = readdir(dip)) != NULL)
			{
				if (dit->d_name[0] != '.')
				{		
					/*
					** add directory name into empty string
					*/
					lists->dest[i] = ft_strdup(arg);
					/*
					** add file name into other emptry string
					*/
					splitstr[i] = ft_strdup(dit->d_name);
					/*
					** combine them together to create a filepath ls_stat can read
					*/
					ft_strcat(lists->dest[i], splitstr[i]);
					/*
					** do actual time_stat()
					** sort array function
					** print returned array with corresponding files
					*/
					lists->timearray[i] = ft_strdup(ft_itoa(time_stat(lists->dest[i])));
					i++;
				}
			}

			/*
			** print off timearray/dest
			*/
			// i = -1;
			// while (++i < lists->filecount)
			// 	printf("before[%d]: %s    %s\n", i, lists->timearray[i], lists->dest[i]);
			/*
			** sort array based on st_mtime
			*/
			ft_switch_time(lists);
			/*
			** print off new array
			*/
			lists->i = -1;
			while (++lists->i < lists->filecount)
			printf("%s\n", lists->dest[lists->i]);
			/*
			** close dir stream
			*/
			if (closedir(dip) == -1)
				ft_error("closedir");
		}
		j++;
	}
	/*
	** TODO: free memory
	*/
}

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
void	list_dira(int argc, char **argv)
{
	DIR				*dip;
	struct dirent	*dit;
	struct stat 	fileStat;
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
			/*
			** TODO: create own function for this because it happens often?
			*/
				if(stat(argv[j],&fileStat) < 0)  
				{
					ft_printf("./ft_ls: %s: No such file or directory\n", argv[j]);
					exit (-1);
				} 
				printf("%s\n", argv[j]);
				exit(1);
			/*
			** end function here?
			*/
		}
		while ((dit = readdir(dip)) != NULL)
			ft_printf("%s\n", dit->d_name);
		if (closedir(dip) == -1)
			ft_error("closedir");
		// j++;
	}
}

/*
** lexicographically sort for ls -r
*/
static void	lex_sort(DIR *dip, t_lists *lists)
{
	int		filecount;
	struct 	dirent *dit;
	char	str[D_NAME_MAX][WORD_MAX];
	char 	temp[WORD_MAX];
	filecount = 0;
	lists->i = 0;

	while ((dit = readdir(dip)) != NULL)
	{
		if (dit->d_name[0] != '.')
		{
			ft_strcpy(str[lists->i], dit->d_name);
			filecount++;
			lists->i++;
		}
	}
	/*
	** TODO: split function here?
	*/
	lists->i = 0;
	while (lists->i < filecount)
	{
		lists->j = lists->i + 1;
		while (lists->j < filecount)
		{
			if (ft_strcmp(str[lists->i], str[lists->j]) < 0)
			{
				ft_strcpy(temp, str[lists->i]);
				ft_strcpy(str[lists->i], str[lists->j]);
				ft_strcpy(str[lists->j], temp);
			}
			lists->j++;
		}
		lists->i++;
	}
	/*
	** TODO: end split function here?
	*/
	lists->i = -1;
	while (++lists->i < filecount)
		printf("%s\n", str[lists->i]);
}

/*
** ls -r
*/
void	list_dirr(int argc, char **argv, t_lists *lists)
{
	DIR				*dip;
	struct stat 	fileStat;
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
        			ft_error(": No such file or directory");
				printf("%s\n", argv[j]);
				exit(1);
		}
		lex_sort(dip, lists);
		if (closedir(dip) == -1)
			ft_error("closedir");
		// j++;
	}
}