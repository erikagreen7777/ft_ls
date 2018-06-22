#include "../ft_ls.h"

/*
** find out how many files are in a directory
*/
int		directory_count(DIR *dip, char *str, int flag)
{
	int		filecount;
	struct 	dirent *dit;
	filecount = 0;

	dip = opendir(str);

	while ((dit = readdir(dip)) != NULL)
	{
		if (flag == 0)
		{
			if (dit->d_name[0] != '.')
				filecount++;
		}
		else if (flag == 1)
			filecount++;
	}
	if (closedir(dip) == -1)
		ft_error("closedir");

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
	char			**splitstr;
	struct stat 	fileStat;
	char			arg[WORD_MAX];
	char 			**array;
	char  			temp[WORD_MAX];

	lists->size = 0;
	lists->i = 0;
	j = 2;
	lists->flag = 0;
	splitstr = NULL;
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
		if(lstat(argv[j], &fileStat) < 0) 
        	ft_error("ls -l: No such file or directory");
    	/*
    	** if it's a regular file
		*/
		if (((fileStat.st_mode & S_IFMT) == S_IFREG) || S_ISLNK(fileStat.st_mode))
			ls_stat(argv[j], lists);
		else if (S_ISDIR(fileStat.st_mode) == 1)
		{
			dip = opendir(argv[j]);
			ft_strcpy(arg, argv[j]);
			if (ft_strcmp(arg, "/dev") == 0)
				lists->flag = 1;
	        /*
	        ** if the last character of argv[j] isn't a "/", add one
	        */
			if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
				ft_strcat(arg, "/");
			if (closedir(dip) == -1)
				ft_error("closedir");
			lists->filecount = directory_count(dip, argv[j], 0);
			dip = opendir(argv[j]);
			/*
			** malloc memory for the 2D array (include extra + 1 for null at end)
			*/
			lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
			array = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
			if (dip == NULL)
			{
				ft_error(": No file or directory");
			}
			ft_strcpy(temp, arg);
			while ((dit = readdir(dip)) != NULL)
			{
				if (dit->d_name[0] != '.')
				{	
					if (lists->i > 0)
						ft_strcpy(arg, temp);
					ft_strcat(arg, dit->d_name);
					lists->dest[lists->i] = ft_strdup(arg);
					ft_bzero(arg, ft_strlen(arg));
					lists->i++;
				}
			}
			/*
			** close dir stream
			*/
			if (closedir(dip) == -1)
				ft_error("closedir");
		}
		j++;
	}
	/*
	** print total 512 block-byte size
	*/
	ls_stat_helper(lists);
	// lists->i = 0;
	// while (lists->i < lists->filecount)
	// {
	// 	lists->size += add_stat(lists->dest[lists->i]);
	// 	lists->i++;
	// }
	// if (lists->size > 0)
	// 	ft_printf("total %d\n", lists->size);
	// else if (lists->flag == 1)
	// 	ft_printf("total 0\n");
	// /*
	// ** print actual ls_stat()
	// */
	// lists->i = -1;
	// while (++lists->i < lists->filecount)
	// 	ls_stat(lists->dest[lists->i], lists);
	/*
	** TODO: free memory
	*/
}


/*
** ls -t
*/
void	list_dirt(int argc, char **argv, t_lists *lists)
{
	int				j;
	DIR				*dip;
	struct dirent	*dit;
	struct stat 	fileStat;
	char			arg[WORD_MAX];
	char  			temp[WORD_MAX];

	lists->i = 0;
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
        	ft_error("ls -t: No such file or directory");
    	/*
    	** if it's a regular file
		*/
		if ((fileStat.st_mode & S_IFMT) == S_IFREG)
			ls_stat(argv[j], lists);
		else if (S_ISDIR(fileStat.st_mode) == 1)
		{
			ft_strcpy(arg, argv[j]);
	        /*
	        ** if the last character of argv[j] isn't a "/", add one
	        */
			if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
				ft_strcat(arg, "/");
			lists->filecount = directory_count(dip, argv[j], 0);
			dip = opendir(argv[j]);
			/*
			** malloc memory for the 2D array (include extra + 1 for null at end)
			*/
			lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
			lists->timearray = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
			if (dip == NULL)
			{
				ft_error(": No file or directory");
			}
			/*
			** TODO: end split function here?
			*/
			ft_strcpy(temp, arg);
			while ((dit = readdir(dip)) != NULL)
			{
				if (dit->d_name[0] != '.')
				{		
					if (lists->i > 0)
						ft_strcpy(arg, temp);
					ft_strcat(arg, dit->d_name);
					lists->dest[lists->i] = ft_strdup(arg);
					ft_bzero(arg, ft_strlen(arg));
					lists->timearray[lists->i] = ft_strdup(ft_itoa(time_stat(lists->dest[lists->i])));
					lists->i++;
				}
			}
			/*
			** sort array based on st_mtime
			*/
			/*
			** print off new array
			*/
			/*
			** close dir stream
			*/
			if (closedir(dip) == -1)
				ft_error("closedir");
		}
		j++;
	}
	ft_switch_time(lists);
	print_lists(lists);
	/*
	** TODO: free memory
	** If the modification time of the file is more than 6 months in the past or
    ** future, then the year of the last modification is displayed in place of
    ** the hour and minute fields.
	*/
	// lists->i = -1;
	// while (++lists->i < lists->filecount)
	// 	ft_printf("%s\n", lists->dest[lists->i]);

}
/*
** lexicographically sort for ls -rl
*/
void	lex_sortrl(t_lists *lists)
{
	char 	*temp;
	lists->i = 0;
	while (lists->i < lists->filecount)
	{
		lists->j = lists->i + 1;
		while (lists->j < lists->filecount)
		{
			if (ft_strcmp(lists->dest[lists->i], lists->dest[lists->j]) < 0)
			{
				temp = ft_strdup(lists->dest[lists->i]);				
				ft_bzero(lists->dest[lists->i], ft_strlen(lists->dest[lists->i]));
				lists->dest[lists->i] = ft_strdup(lists->dest[lists->j]);
				ft_bzero(lists->dest[lists->j], ft_strlen(lists->dest[lists->j]));
				lists->dest[lists->j] = ft_strdup(temp);
				ft_bzero(temp, ft_strlen(temp));
			}
			lists->j++;
		}
		lists->i++;
	}
}
/*
** - reverse lexicographically sort for -rla
*/
void	rlex_sortrl(t_lists *lists)
{
	char 	*temp;
	lists->i = 0;
	while (lists->i < lists->filecount)
	{
		lists->j = lists->i + 1;
		while (lists->j < lists->filecount)
		{
			/*
			** - the next line is different than the previous function. add flag?
			*/
			if (ft_strcmp(lists->dest[lists->i], lists->dest[lists->j]) > 0)
			{
				temp = ft_strdup(lists->dest[lists->i]);				
				ft_bzero(lists->dest[lists->i], ft_strlen(lists->dest[lists->i]));
				lists->dest[lists->i] = ft_strdup(lists->dest[lists->j]);
				ft_bzero(lists->dest[lists->j], ft_strlen(lists->dest[lists->j]));
				lists->dest[lists->j] = ft_strdup(temp);
				ft_bzero(temp, ft_strlen(temp));
			}
			lists->j++;
		}
		lists->i++;
	}
}
/*
** lexicographically sort for ls -r
*/
void	lex_sort(t_lists *lists)
{
	char 	*temp;
	lists->i = 0;
	while (lists->i < lists->filecount)
	{
		lists->j = lists->i + 1;
		while (lists->j < lists->filecount)
		{
			if (ft_strcmp(lists->dest[lists->i], lists->dest[lists->j]) < 0)
			{
				temp = ft_strdup(lists->dest[lists->i]);				
				ft_bzero(lists->dest[lists->i], ft_strlen(lists->dest[lists->i]));
				lists->dest[lists->i] = ft_strdup(lists->dest[lists->j]);
				ft_bzero(lists->dest[lists->j], ft_strlen(lists->dest[lists->j]));
				lists->dest[lists->j] = ft_strdup(temp);
				ft_bzero(temp, ft_strlen(temp));
			}
			lists->j++;
		}
		lists->i++;
	}
	print_lists(lists);
	// lists->i = -1;
	// while (++lists->i < lists->filecount)
	// 	printf("%s\n", lists->dest[lists->i]);
	// exit(1);
}

/*
** ls -r
*/
void	list_dirr(int argc, char **argv, t_lists *lists)
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
		lists->filecount = directory_count(dip, argv[j], 0);
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
			if (dit->d_name[0] != '.')
			{	
				if (lists->i > 0)
					ft_strcpy(arg, temp);
				ft_strcat(arg, dit->d_name);
				lists->dest[lists->i] = ft_strdup(arg);
				ft_bzero(arg, ft_strlen(arg));
				lists->i++;
			}
		}
		if (closedir(dip) == -1)
			ft_error("closedir");
		lex_sort(lists);
	}
}