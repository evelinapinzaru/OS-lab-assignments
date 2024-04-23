#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void parcurge_proceseaza(char *surs, char *dest) {
  DIR *dir_surs, *dir_dest;
  struct stat stare_d_surs;
  stat(surs, &stare_d_surs);
  struct stat stare_d_dest;
  struct dirent *date_intr;

  // deschidere (eventual, creare) directoare
  if(!(dir_surs = opendir(surs))) {
    perror("Eroare la deschiderea unui director sursa!");
    exit(EXIT_FAILURE);
  }

  if(stat(dest, &stare_d_dest) < 0) {
    if(mkdir(dest, stare_d_surs.st_mode) < 0) {
      perror("Eroare la crearea unui director destinatie!");
      exit(EXIT_FAILURE);
    }
  }

  if(!(dir_dest = opendir(dest))) {
    perror("Eroare la deschiderea unui director destinatie!");
    exit(EXIT_FAILURE);
  }

  // parcurgere director sursa si procesare a elementelor (directoare/fisiere) continute de acesta
  while(date_intr = readdir(dir_surs)) {
    char surs_cale[PATH_MAX], dest_cale[PATH_MAX];
    snprintf(surs_cale, sizeof(surs_cale), "%s/%s", surs, date_intr->d_name);
    snprintf(dest_cale, sizeof(dest_cale), "%s/%s", dest, date_intr->d_name);

    if(date_intr->d_type == DT_DIR && strcmp(date_intr->d_name, ".") != 0 && strcmp(date_intr->d_name, "..") != 0) {
      parcurge_proceseaza(surs_cale, dest_cale);
    }else if(date_intr->d_type == DT_REG) {
      struct stat date_intr_stat;
      stat(surs_cale, &date_intr_stat);

      if(date_intr_stat.st_size < 500) {
        int s_file = open(surs_cale, O_RDONLY);
        if(s_file < 0) {
          perror("Eroare la deschiderea unui fisier sursa!");
          exit(EXIT_FAILURE);
        }

        int d_file = creat(dest_cale, 0777);
        if(d_file < 0) {
          perror("Eroare la crearea/deschiderea unui fisier destinatie!");
          exit(EXIT_FAILURE);
        }

        char buf[PATH_MAX];
        ssize_t octeti_cititi;
        while((octeti_cititi = read(s_file, buf, sizeof(buf))) > 0) {
          write(d_file, buf, octeti_cititi);
        }

        fchmod(d_file, date_intr_stat.st_mode & 0444);
        close(s_file);
        close(d_file);
      }else{
        char bufi[PATH_MAX];
        symlink(realpath(surs_cale, bufi), dest_cale);
      }
    }
  }

  // inchidere directoare
  closedir(dir_surs);
  closedir(dir_dest);
}
