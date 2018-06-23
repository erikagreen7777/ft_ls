#include "../ft_ls.h"

/*
** -aother backwards helper
*/
void	back_helper(t_lists *lists)
{
	lists->i = 0;
	while (lists->i < lists->filecount)
	{
		lists->size += add_stat(lists->dest[lists->i]);
		lists->i++;
	}
	if (lists->size > 0)
		ft_printf("total %d\n", lists->size);
	else if (lists->flag == 1)
		ft_printf("total 0\n");
	lists->i = lists->filecount;
	while (--lists->i > -1)
	{
		ls_stat(lists->dest[lists->i], lists);
	}
}
/*
** -recursive lstat() helpers
*/
void 	recursive_ls_stat_helper(t_lists *lists)
{
    lists->i = 0;
    while (lists->i < lists->filecount)
    {
        lists->size += add_stat(lists->dest[lists->i]);
        lists->i++;
    }
    ft_printf("total %d\n", lists->size);
    if (lists->flag == 1)
        ft_printf("total 0\n");
    /*
    ** print actual ls_stat()
    */
    lists->i = -1;
    while (++lists->i < lists->filecount)
        ls_stat(lists->dest[lists->i], lists);
}

/*
** - recurstive lstat() helper for -r
*/
void 	r_recursive_ls_stat_helper(t_lists *lists)
{
	lists->i = -1;
    while (++lists->i < lists->filecount)
        lists->size += add_stat(lists->dest[lists->i]);
    ft_printf("total %d\n", lists->size);
    if (lists->flag == 1)
        ft_printf("total 0\n");
    /*
    ** feed into lstat() backwards to get -r
    */
    lists->i = lists->filecount;
    while (--lists->i > -1)
        ls_stat(lists->dest[lists->i], lists);
}

/*
** -lstat()_helper
*/
void	ls_stat_helper(t_lists *lists)
{
	int 			size;

	size = 0;
	/*
	** print total 512 block-byte size
	*/
	lists->i = 0;
	while (lists->i < lists->filecount)
	{
		size += add_stat(lists->dest[lists->i]);
		lists->i++;
	}
	if (size > 0)
		ft_printf("total %d\n", size);
	else if (lists->flag == 1)
		ft_printf("total 0\n");
	/*
	** print actual ls_stat()
	*/
	lists->i = -1;
	while (++lists->i < lists->filecount)
		ls_stat(lists->dest[lists->i], lists);
}

void 	ls_la(int argc, char **argv, t_lists *lists)
{
	int				j;
	DIR				*dip;
	// struct dirent	*dit;
	char			**splitstr;
	struct stat 	fileStat;
	char			arg[WORD_MAX];
	// char 			**array;
	// char  			temp[WORD_MAX];

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
			lists->filecount = directory_count(dip, argv[j], 1);
			dip = opendir(argv[j]);
			/*
			** malloc memory for the 2D array (include extra + 1 for null at end)
			*/
			read_helper_a(lists, 0, arg, dip);
			// lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
			// array = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
			// if (dip == NULL)
			// {
			// 	ft_error(": No file or directory");
			// }
			// ft_strcpy(temp, arg);
			// while ((dit = readdir(dip)) != NULL)
			// {
			// 		if (lists->i > 0)
			// 			ft_strcpy(arg, temp);
			// 		ft_strcat(arg, dit->d_name);
			// 		lists->dest[lists->i] = ft_strdup(arg);
			// 		ft_bzero(arg, ft_strlen(arg));
			// 		lists->i++;
			// }
			/*
			** close dir stream
			*/
			if (closedir(dip) == -1)
				ft_error("closedir");
		}
		j++;
	}
	ls_stat_helper(lists);
}
/*
** -lt / -tl
*/
void 					ls_lt(int argc, char **argv, t_lists *lists)
{
	int				j;
	DIR				*dip;
	char			**splitstr;
	struct stat 	fileStat;
	char			arg[WORD_MAX];
	// int 			size;

	// size = 0;
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
			read_helper(lists, 1, arg, dip);
			// lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
			// array = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
			// lists->timearray = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
			// if (dip == NULL)
			// {
			// 	ft_error(": No file or directory");
			// }
			// ft_strcpy(temp, arg);
			// while ((dit = readdir(dip)) != NULL)
			// {
			// 	if (dit->d_name[0] != '.')
			// 	{	
			// 		if (lists->i > 0)
			// 			ft_strcpy(arg, temp);
			// 		ft_strcat(arg, dit->d_name);
			// 		lists->dest[lists->i] = ft_strdup(arg);
			// 		ft_bzero(arg, ft_strlen(arg));
			// 		lists->timearray[lists->i] = ft_strdup(ft_itoa(time_stat(lists->dest[lists->i])));
			// 		lists->i++;
			// 	}
			// }
			/*
			** close dir stream
			*/
			if (closedir(dip) == -1)
				ft_error("closedir");
		}
		j++;
	}
	ft_switch_time(lists);
	ls_stat_helper(lists);
}

/*
** -lta
*/
void 					ls_lta(int argc, char **argv, t_lists *lists)
{
	int				j;
	DIR				*dip;
	// struct dirent	*dit;
	char			**splitstr;
	struct stat 	fileStat;
	char			arg[WORD_MAX];
	int 			size;
	// char 			**array;
	// char  			temp[WORD_MAX];

	size = 0;
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
			lists->filecount = directory_count(dip, argv[j], 1);
			dip = opendir(argv[j]);
			/*
			** malloc memory for the 2D array (include extra + 1 for null at end)
			*/
			read_helper_a(lists, 1, arg, dip);
			// lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
			// array = (char **)ft_memalloc(sizeof(char *) * lists->filecount  + 1);
			// lists->timearray = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
			// if (dip == NULL)
			// {
			// 	ft_error(": No file or directory");
			// }
			// ft_strcpy(temp, arg);
			// while ((dit = readdir(dip)) != NULL)
			// {
			// 		if (lists->i > 0)
			// 			ft_strcpy(arg, temp);
			// 		ft_strcat(arg, dit->d_name);
			// 		lists->dest[lists->i] = ft_strdup(arg);
			// 		ft_bzero(arg, ft_strlen(arg));
			// 		lists->timearray[lists->i] = ft_strdup(ft_itoa(time_stat(lists->dest[lists->i])));
			// 		lists->i++;
			// }
			ft_switch_time(lists);
			/*
			** close dir stream
			*/
			if (closedir(dip) == -1)
				ft_error("closedir");
		}
		j++;
	}
	ls_stat_helper(lists);

}

/*
** - at
*/
void			list_dirta(int argc, char **argv, t_lists *lists)
{
	int				j;
	DIR				*dip;
	// struct dirent	*dit;
	struct stat 	fileStat;
	char			arg[WORD_MAX];
	// char  			temp[WORD_MAX];

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
			read_helper_a(lists, 1, arg, dip);
			// lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
			// lists->timearray = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
			// if (dip == NULL)
			// {
			// 	ft_error(": No file or directory");
			// }
			// /*
			// ** TODO: end split function here?
			// */
			// ft_strcpy(temp, arg);
			// while ((dit = readdir(dip)) != NULL)
			// {	
			// 		if (lists->i > 0)
			// 			ft_strcpy(arg, temp);
			// 		ft_strcat(arg, dit->d_name);
			// 		lists->dest[lists->i] = ft_strdup(arg);
			// 		ft_bzero(arg, ft_strlen(arg));
			// 		lists->timearray[lists->i] = ft_strdup(ft_itoa(time_stat(lists->dest[lists->i])));
			// 		lists->i++;
			// }
			/*
			** sort array based on st_mtime
			*/
			ft_switch_time(lists);
			if (closedir(dip) == -1)
				ft_error("closedir");
		}
		j++;
	}
	lists->i = -1;
	while (++lists->i < lists->filecount)
		ft_printf("%s\n", lists->dest[lists->i]);

}
