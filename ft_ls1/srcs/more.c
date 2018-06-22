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


/*
** ls -rt/ -tr
*/
void 					ls_rt(int argc, char **argv, t_lists *lists)
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
			// dip = opendir(argv[j]);
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
			ft_switch_time(lists);
			if (closedir(dip) == -1)
				ft_error("closedir");
		}
		j++;
	}
	print_lists_back(lists);
	// lists->i = lists->filecount - 1;
	// while (lists->i > -1)
	// {
	// 	printf("%s\n", lists->dest[lists->i]);
	// 	lists->i--;
	// }
}

/*
** ls -rat
*/
void 					ls_rat(int argc, char **argv, t_lists *lists)
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
			lists->filecount = directory_count(dip, argv[j], 1);
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
					if (lists->i > 0)
						ft_strcpy(arg, temp);
					ft_strcat(arg, dit->d_name);
					lists->dest[lists->i] = ft_strdup(arg);
					ft_bzero(arg, ft_strlen(arg));
					lists->timearray[lists->i] = ft_strdup(ft_itoa(time_stat(lists->dest[lists->i])));
					lists->i++;
			}
			ft_switch_time(lists);
			if (closedir(dip) == -1)
				ft_error("closedir");
		}
		j++;
	}
	print_lists_back(lists);
	// lists->i = lists->filecount - 1;
	// while (lists->i > -1)
	// {
	// 	printf("%s\n", lists->dest[lists->i]);
	// 	lists->i--;
	// }
}

/*
** ls -lrat
*/
void 					ls_lrat(int argc, char **argv, t_lists *lists)
{
	int				j;
	DIR				*dip;
	struct dirent	*dit;
	struct stat 	fileStat;
	char			arg[WORD_MAX];
	char  			temp[WORD_MAX];

	lists->size = 0;
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
		if(lstat(argv[j], &fileStat) < 0) 
        	ft_error("ls -l: No such file or directory");
    	/*
    	** if it's a regular file
		*/
		if (((fileStat.st_mode & S_IFMT) == S_IFREG) || S_ISLNK(fileStat.st_mode))
			ls_stat(argv[j], lists);		
		else if (S_ISDIR(fileStat.st_mode) == 1)
		{
			ft_strcpy(arg, argv[j]);
	        /*
	        ** if the last character of argv[j] isn't a "/", add one
	        */
			if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
				ft_strcat(arg, "/");
			lists->filecount = directory_count(dip, argv[j], 1);
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
					if (lists->i > 0)
						ft_strcpy(arg, temp);
					ft_strcat(arg, dit->d_name);
					lists->dest[lists->i] = ft_strdup(arg);
					ft_bzero(arg, ft_strlen(arg));
					lists->timearray[lists->i] = ft_strdup(ft_itoa(time_stat(lists->dest[lists->i])));
					lists->i++;
			}
			if (closedir(dip) == -1)
				ft_error("closedir");
		}
		j++;
	}
	ft_switch_time(lists);
	back_helper(lists);
}
