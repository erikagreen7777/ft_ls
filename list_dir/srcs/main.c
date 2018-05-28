//how is the j going to work for parsing arguments like -a and -l? 



#include "../ft_ls.h"

int main(int argc, char **argv)
{
	DIR				*dip;
	struct dirent	*dit;
	int 			i;
	int				j;

	i = 0;

	j = 1;
	//error usage
	if (argc < 2)
	{
		ft_printf("Usage: %s <directory>\n", argv[0]);
		return (1);
	}

	//to account for multiple directory lses
	while (j < argc)
	{
		if (j > 1 && j < argc)
			write(1, "\n", 1);
		//open directory (argv[1])
		dip = opendir(argv[j]);
		if (dip == NULL)
		{
			perror("opendir");
			return (1);
		}

		//read directories and print
		while ((dit = readdir(dip)) != NULL)
		{
			if (dit->d_name[0] != '.')
				ft_printf("%s\n", dit->d_name);
			i++;
		}

		//total number of files
		// ft_printf("readdir() found a total of %i files\n", i);

		//close directories
		if (closedir(dip) == -1)
		{
			perror("closedir");
			return (1);
		}
		j++;
	}


	return (0);
}

