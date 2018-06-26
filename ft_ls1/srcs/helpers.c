#include "../ft_ls.h"
/*
** - normed extra read helper for -as
*/
void				read_helper_guts_a(t_lists *lists, char *arg, struct dirent *dit, char *temp, int flag)
{
	char 	*temptwo;
	temptwo = NULL;

	if (lists->i > 0)
		ft_strcpy(arg, temp);
	ft_strcat(arg, dit->d_name);
	lists->dest[lists->i] = ft_strdup(arg);
	ft_bzero(arg, ft_strlen(arg));
	if (flag == 1)
	{
		lists->timearrayflag++;
		temptwo = ft_itoa(time_stat(lists->dest[lists->i]));
		lists->timearray[lists->i] = ft_strdup(temptwo);
		ft_bzero(temptwo, ft_strlen(temptwo));
		free(temptwo);	
	}
	lists->i++;
}
/*
** -normed extra read helper
*/
void				read_helper_guts(t_lists *lists, char *arg, struct dirent *dit, char *temp, int flag)
{
	char 	*temptwo;
	temptwo = NULL;

	if (dit->d_name[0] != '.')
	{
		if (lists->i > 0)
			ft_strcpy(arg, temp);
		ft_strcat(arg, dit->d_name);
		lists->dest[lists->i] = ft_strdup(arg);
		ft_bzero(arg, ft_strlen(arg));
		if (flag == 1)
		{
			lists->timearrayflag++;
			temptwo = ft_itoa(time_stat(lists->dest[lists->i]));
			lists->timearray[lists->i] = ft_strdup(temptwo);
			ft_bzero(temptwo, ft_strlen(temptwo));
			free(temptwo);
		}
		lists->i++;
	}
	// char 	*temptwo;
	// temptwo = NULL;

	// if (dit->d_name[0] != '.')
	// {
	// 	if (lists->i > 0)
	// 		ft_strcpy(arg, temp);
	// 	ft_strcat(arg, dit->d_name);
	// 	lists->dest[lists->i] = ft_strdup(arg);
	// 	ft_bzero(arg, ft_strlen(arg));
	// 	if (flag == 1)
	// 	{
	// 		lists->timearrayflag++;
	// 		temptwo = ft_itoa(time_stat(lists->dest[lists->i]));
	// 		lists->timearray[lists->i] = ft_strdup(temptwo);
	// 		ft_bzero(temptwo, ft_strlen(temptwo));
	// 		free(temptwo);
	// 	}
	// 	lists->i++;
	// }
}
/*
** -read helper for most of the functions
*/
void				read_helper(t_lists *lists, int flag, char *arg, DIR *dip)
{
	char			temp[WORD_MAX];
	struct dirent	*dit;
	
	lists->dest = (char **)ft_memalloc(sizeof(char *) * (lists->filecount + 1));
	if (flag == 1)
	{
		lists->timearrayflag++;
		lists->timearray = (char **)ft_memalloc(sizeof(char *) * (lists->filecount + 1));
	}
	if (dip == NULL)
	{
		ft_error(": No file or directory");
	}
	ft_strcpy(temp, arg);
	while ((dit = readdir(dip)) != NULL)
	{
		read_helper_guts(lists, arg, dit, temp, flag);
	}

}
/*
** -read helper for -a
*/
void				read_helper_a(t_lists *lists, int flag, char *arg, DIR *dip)
{
	char			temp[WORD_MAX];
	struct dirent	*dit;
	
	lists->dest = (char **)ft_memalloc(sizeof(char *) * (lists->filecount  + 1));
	if (flag == 1)
	{
		lists->timearray = (char **)ft_memalloc(sizeof(char *) * (lists->filecount + 1));
		lists->timearrayflag++;
	}
	if (dip == NULL)
	{
		ft_error(": No file or directory");
	}
	ft_strcpy(temp, arg);
	while ((dit = readdir(dip)) != NULL)
	{
		read_helper_guts_a(lists, arg, dit, temp, flag);
	}

}
/*
** - print lists
*/
void				print_lists(t_lists *lists)
{
	lists->i = -1;
	while (++lists->i < lists->filecount)
		ft_printf("%s\n", lists->dest[lists->i]);
}
