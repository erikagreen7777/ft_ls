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
	struct stat 	fileStat;
	char			arg[WORD_MAX];

/* ------------------------------------------> */
	lists->size = 0;
	lists->i = 0;
	j = 1;
	lists->flag = 0;
	if (argc == 2)
	{
		argv[j + 1] = ".";
		argc = 3;
	}
/* ------------------------------------------> */		
	while (++j < argc)
	{
		if(lstat(argv[j], &fileStat) < 0) 
        	ft_error("ls -l: No such file or directory");
		if (((fileStat.st_mode & S_IFMT) == S_IFREG) || S_ISLNK(fileStat.st_mode))
			ls_stat(argv[j], lists);
		else if (S_ISDIR(fileStat.st_mode) == 1)
		{
			dip = opendir(argv[j]);
			ft_strcpy(arg, argv[j]);
			if (ft_strcmp(arg, "/dev") == 0)
				lists->flag = 1;
			if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
				ft_strcat(arg, "/");
			if (closedir(dip) == -1)
				ft_error("closedir");
			lists->filecount = directory_count(dip, argv[j], 0);
			dip = opendir(argv[j]);
			read_helper(lists, 0, arg, dip);
			if (closedir(dip) == -1)
				ft_error("closedir");
		}
	}
	ls_stat_helper(lists);
}


/*
** ls -t
*/
void	list_dirt(int argc, char **argv, t_lists *lists)
{
	int				j;
	DIR				*dip;
	struct stat 	fileStat;
	char			arg[WORD_MAX];
/* --------------------------------------------> */
	lists->i = 0;
	j = 1;
	if (argc == 2)
	{
		argv[j + 1] = ".";
		argc = 3;
	}
/* --------------------------------------------> */
	while (++j < argc)
	{
		if(lstat(argv[j], &fileStat) < 0) 
        	ft_error("ls -t: No such file or directory");
		if ((fileStat.st_mode & S_IFMT) == S_IFREG)
			ls_stat(argv[j], lists);
		else if (S_ISDIR(fileStat.st_mode) == 1)
		{
			ft_strcpy(arg, argv[j]);
			if (ft_strcmp(&arg[ft_strlen(arg) - 1], "/") != 0)
				ft_strcat(arg, "/");
			lists->filecount = directory_count(dip, argv[j], 0);
			dip = opendir(argv[j]);
			read_helper(lists, 1, arg, dip);
			if (closedir(dip) == -1)
				ft_error("closedir");
		}
	}
	ft_switch_time(lists);
	print_lists(lists);
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
}
