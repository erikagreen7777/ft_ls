#include "../ft_ls.h"


int main(int argc, char **argv)
{

	if (ft_strcmp(argv[0], "./ft_ls") == 0)
	{
		if (argc < 2)
			ft_error("Usage: ./ft_ls [-options] <file or folder>");
		if (ft_strcmp(argv[1], "-a") == 0)
		{
			if (argc < 3)
				ft_error("Usage: ./ft_ls -a <directory>");
			list_dira(argc, argv);
		}
		else if (ft_strcmp(argv[1], "-l") == 0)
		{
			if (argc < 3)
				ft_error("Usage: ./ft_ls -l <directory>");
			list_dirl(argc, argv);
			// ls_stat(argv[2]);
		}
		else if (ft_strcmp(argv[1], "-r") == 0)
		{
			if (argc < 3)
				ft_error("Usage: ./ft_ls -r <directory>");
			list_dirr(argc, argv);
		}
		else if (ft_strcmp(argv[1], "-R") == 0)
		{
			if (argc < 3)
				ft_error("Usage: ./ft_ls -R <directory>");
			list_dirbigr(argv[2]);
		}
		else
		{
			list_dir(argc, argv);
		}
	}
	return (0);
}