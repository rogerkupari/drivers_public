#include <stdio.h>
#include <string.h>
#include "ohjaus.h"



int main(int argc, char *argv[])
{

	if(argc != 3)
	{
		printf("virhe, ohjaus on muotoa: led numero \n");
		return -1;
	}
	if(strcmp(argv[1], "led")!=0)
	{
		printf("Virhe, ensimmainen argumentti oltava 'led' \n");
		return -1;
	}

	if((strcmp(argv[2], "1")!=0) && (strcmp(argv[2], "0")!=0))
	{
		printf("Virhe, toinen argumentti oltava '1' tai '0' %s \n", argv[2]);
                return -1;

	}

	toteuta(argv);
	return 0;

}
