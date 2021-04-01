#include<stdio.h>
#include"list.h"
#include"huffman.h"

int main(int argc, char **argv)
{
	FILE *fd;
	(void)argc;
	if( 'c' == argv[1][0])
	{
		fd = fopen(argv[2],"rb");
		if(fd == NULL)
		{
			perror("Error");
			exit(1);
		}
		compress(fd);
	}
	else if( 'd' == argv[1][0])
	{
		fd = fopen(argv[2],"rb");
		if(fd == NULL)
		{
			perror("Error");
			exit(1);
		}
		decompress(fd);
	}
	else
	{
		printf("Usage: ./%s (d(decompresser) ou c(compresser)) nom_du_fichier_a_compresser ou decompresser\n", argv[0]);
		exit(1);
	}
	fclose(fd);
	return(0);
}