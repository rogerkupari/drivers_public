#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>




void toteuta(char *komento[])
{


	int tiedosto = open("/dev/led", O_WRONLY);

	if(tiedosto < 0)
	{
		printf("/dev/led - ei voida avata, tarkista tiedoston nimi; suoritettava paakayttajan oikeuksin \n");

	}


	if(write(tiedosto, komento[2], 1) < 0)
	{
		printf("virhe kirjoitettaessa komentoa /dev/led \n");
	}


	printf("komento suoritettu \n");

}
