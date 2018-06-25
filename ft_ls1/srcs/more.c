#include "../ft_ls.h"

/*
** ls -rt/ -tr
*/
void 					ls_rt(/*int argc, */char **argv, t_lists *lists)
{
	int				j;
	DIR				*dip;
	struct dirent	*dit;
	struct stat 	fileStat;
	char			arg[WORD_MAX];
	char  			temp[WORD_MAX];

	j = lists->argcount;
	while (j < lists->newargc)
	{
		if (j > lists->argcount && j < lists->newargc)
			write(1, "\n", 1);
		lists->i = 0;
		if(stat(argv[j], &fileStat) < 0) 
        	ft_error("ls -t: No such file or directory");
		if ((fileStat.st_mode & S_IFMT) == S_IFREG)
			ls_stat(argv[j], lists);
		else if (S_ISDIR(fileStat.st_mode) == 1)
		{
			// dip = opendir(argv[j]);
			ft_strcpy(arg, argv[j]);
			if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
				ft_strcat(arg, "/");
			lists->filecount = directory_count(dip, argv[j], 0);
			dip = opendir(argv[j]);
			lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
			lists->timearray = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
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
					lists->timearray[lists->i] = ft_strdup(ft_itoa(time_stat(lists->dest[lists->i])));
					lists->i++;
				}
			}
			ft_switch_time(lists);
			if (closedir(dip) == -1)
				ft_error("closedir");
			print_lists_back(lists);

		}
		j++;
	}
}
/*
** - ls -rat helper
*/
static void 	ls_rat_helper(char *str, t_lists *lists, DIR *dip)
{
	char			arg[WORD_MAX];
	char  			temp[WORD_MAX];
	struct dirent	*dit;

	ft_strcpy(arg, str);
	if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
		ft_strcat(arg, "/");
	lists->filecount = directory_count(dip, str, 1);
	dip = opendir(str);
	lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
	lists->timearray = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
	if (dip == NULL)
		ft_error(": No file or directory");
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

/*
** ls -rat
*/
void 					ls_rat(char **argv, t_lists *lists)
{
	int				j;
	struct stat 	fileStat;
	DIR				*dip;

	dip = NULL;
	j = lists->argcount;
	while (j < lists->newargc)
	{
		if (j > lists->argcount && j < lists->newargc)
			write(1, "\n", 1);
		lists->i = 0;
		if(stat(argv[j], &fileStat) < 0) 
        	ft_error("ls -t: No such file or directory");
		if ((fileStat.st_mode & S_IFMT) == S_IFREG)
			ls_stat(argv[j], lists);
		else if (S_ISDIR(fileStat.st_mode) == 1)
		{
			ls_rat_helper(argv[j], lists, dip);
			ft_switch_time(lists);
			print_lists_back(lists);
		}
		j++;
	}
}

/*
** ls -lrat
*/
void 					ls_lrat(char **argv, t_lists *lists)
{
	int				j;
	DIR				*dip;
	struct dirent	*dit;
	struct stat 	fileStat;
	char			arg[WORD_MAX];
	char  			temp[WORD_MAX];

    j = lists->argcount;
    while (j < lists->newargc)
    {
        if (j > lists->argcount && j < lists->newargc)
            write(1, "\n", 1);
		lists->i = 0;
		if(lstat(argv[j], &fileStat) < 0) 
        	ft_error("ls -l: No such file or directory");
		if (((fileStat.st_mode & S_IFMT) == S_IFREG) || S_ISLNK(fileStat.st_mode))
			ls_stat(argv[j], lists);		
		else if (S_ISDIR(fileStat.st_mode) == 1)
		{
			ft_strcpy(arg, argv[j]);
			if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
				ft_strcat(arg, "/");
			lists->filecount = directory_count(dip, argv[j], 1);
			dip = opendir(argv[j]);
			lists->dest = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
			lists->timearray = (char **)ft_memalloc(sizeof(char *) * lists->filecount + 1);
			if (dip == NULL)
			{
				ft_error(": No file or directory");
			}
			ft_strcpy(temp, arg);
			while ((dit = readdir(dip)) != NULL)
			{	
				read_helper_guts_a(lists, arg, dit, temp, 1);
				// if (lists->i > 0)
				// 	ft_strcpy(arg, temp);
				// ft_strcat(arg, dit->d_name);
				// lists->dest[lists->i] = ft_strdup(arg);
				// ft_bzero(arg, ft_strlen(arg));
				// lists->timearray[lists->i] = ft_strdup(ft_itoa(time_stat(lists->dest[lists->i])));
				// lists->i++;
			}
			if (closedir(dip) == -1)
				ft_error("closedir");
			ft_switch_time(lists);
			back_helper(lists);
		}
		j++;
	}
}
