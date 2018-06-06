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
void	list_dirl(int argc, char **argv)
{
	int				j;
	DIR				*dip;
	struct dirent	*dit;
	char			splitstr[WORD_MAX][D_NAME_MAX];
	int				i;
	struct stat 	fileStat;
	int				filecount;
	char			dest[WORD_MAX][D_NAME_MAX];
	char			arg[WORD_MAX];
	int 			size;

	size = 0;
	i = 0;
	j = 2;
	dest = NULL;
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

					dest[i] = ft_strcpy(arg);

					splitstr[i] = ft_strcpy(dit->d_name);
	
					ft_strcat(dest[i], splitstr[i]);
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
		size += add_stat(dest[i]);
	ft_printf("total %d\n", size);

	i = -1;
	while (++i < filecount)
		ls_stat(dest[i]);
}

