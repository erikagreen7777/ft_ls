#include "../ft_ls.h"

int main(int argc, char **argv)
{
	DIR		*dip;
	struct dirent	*dit;

	int i = 0;

	if (argc < 2)
	{
		ft_printf("Usage: %s <director>\n", argv[0]);
		return (0);
	}

	if ((dip = opendir(argv[1])) == NULL)
	{
		perror("opendir");
		return (0);
	}

	while ((dit = readdir(dip)) != NULL)
	{
		i++;
		ft_printf("\n%s", dit->d_name);
	}

	ft_printf("\n\nreaddir() found a total of %i files\n", i);

	if (closedir(dip) == -1)
	{
		perror("closedir");
		return (0);
	}

	return (1);
}

