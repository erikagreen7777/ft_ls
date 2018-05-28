#include "../ft_ls.h"


int main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_printf("Usage: %s <directory>\n", argv[0]);
		return (1);
	}
	//just ./ft_ls <directory>
	if (ft_strcmp(argv[0], "./ft_ls") == 0)
	{
		if (ft_strcmp(argv[1], "-a") == 0)
		{
			list_dira(argc, argv);
		}
		else
		{
			list_dir(argc, argv);
		}
	}
	else
		printf("Nope\n");
	return (0);
}