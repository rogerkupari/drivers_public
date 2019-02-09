#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/*///////////////////////////////////
**  character_led/uspace/toiminto.c**
**  Author: Roger Kupari           **
**  date: 09.02.2019               **
*////////////////////////////////////




void toteuta(char *komento[])
{

	// char devin osoite, vain kirjoitus sallittu (moduulissa ei ole alustettu muita toimintoja)
	int tiedosto = open("/dev/led", O_WRONLY);

	// kayttajan tulee suorittaa tiedosto paakayttajan oikeuksin
	if(tiedosto < 0)
	{
		printf("/dev/led - ei voida avata, tarkista tiedoston nimi; suoritettava paakayttajan oikeuksin \n");

	}

	// valitetaan eteenpain nyt tassa tapauksessa vain 1/0, silla ohjattavana on yksi ledi 
	if(write(tiedosto, komento[2], 1) < 0)
	{
		printf("virhe kirjoitettaessa komentoa /dev/led \n");
	}


	printf("komento suoritettu \n");

}
