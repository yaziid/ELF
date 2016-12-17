/*
	Coded by Yaziid, j'adore le C et la programmation systeme sous UNIX !
	Un petit programme qui affiche les différentes informations relative au fichier ELF (Equivalent du PE de windaube :p)
	Fonctions nouvellement apprises: mmap(), munmap() .
	Structures nouvellement apprises: Elf64_Ehdr .

	Commandes:
		Compilation: gcc mmap.c -o mmap
		Tester que le programme affiche les bonnes informations: readelf -h test

	Programme pouvant être largement amélioré, notamment au niveau du fichier a ouvrir, on peut le faire passer en parametre via la ligne de commande .
	Il faut aussi penser a rajouter un test pour voir que le fichier qu'on a est bien un ELF grace au 4 premiers octects du fichier !

	Samedi 17 décembre 2016, 11h50 .
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <elf.h>
#include <sys/stat.h>

void elf_print_header(Elf64_Ehdr * data)
{
  printf("Point d'entree                               : %p\n", data->e_entry);
  printf("Adresse de la table des segments (relative)  : + %4d bytes\n", data->e_phoff);
  printf("Nombre d'elements dans la table des segments : %d\n", data->e_phnum);
  printf("Adresse de la table des segments (relative)  : + %4d bytes\n", data->e_shoff);
  printf("Nombre d'elements dans la table des sections : %d\n", data->e_shnum);
}

int main(int argc, char ** argv)
{
	int fd = -1;
	void * data = NULL;
	struct stat f_info;
	
	if((fd = open("test", O_RDONLY)) > 0) // si le fichier est bien ouvert
	{
		if(!fstat(fd, &f_info)) // recupere les infos du fichier
		{
			if((data  = mmap(NULL, f_info.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) != MAP_FAILED) // on map !
			{
				elf_print_header((Elf64_Ehdr*) data); // un petit cast s'impose car le retourne de mmap est un (void *)

				/* Place au jeu ici :D */
				
				/*Fin*/

				munmap(data, f_info.st_size);
			}
			else printf("\nError mmap\n");
		}else printf("\nError fstat\n");
	}else printf("\nError open\n");
	
	close(fd);

	return 0;
}
