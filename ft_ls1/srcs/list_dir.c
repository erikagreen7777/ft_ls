#include "../ft_ls.h"

char	*extract_path(char *str)
{
	int				len;
	char			*newstr;

	newstr = (char *)malloc(sizeof(char));
	len = ft_strlen(str) - ft_strlen(ft_strstr(str, "/"));
	ft_strncpy(newstr, str, len);
	// printf("newstr: %s\n", newstr);
	return (newstr);

}

void	list_dir(int argc, char **argv)
{
	DIR				*dip;
	struct dirent	*dit;
	int 			i;
	int				j;
	i = 0;
	j = 1;
	while (j < argc)
	{
		if (j > 1 && j < argc)
			write(1, "\n", 1);
		//check for whether it's a directory or file here
		// you're going to need another function to do that
		dip = opendir(argv[j]);
		if (dip == NULL)
		{
			// extract_path(argv[j]);
			if ((dip = opendir(extract_path(argv[j]))) != NULL)
				{
					printf("%s\n", argv[j]);
					exit(0);
				}
			else
				ft_error("opendir");
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
	int 			i;
	int				j;
	i = 0;
	j = 2;
	while (j < argc)
	{
		if (j > 2 && j < argc)
			write(1, "\n", 1);
		//check for whether it's a directory or file here
		// you're going to need another function to do that
		dip = opendir(argv[j]);
		if (dip == NULL)
			ft_error("opendir");
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