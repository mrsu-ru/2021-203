#include <cstdlib>
#include <cstring>
#include "lab.h"
#include <iostream>
#include "akishevdv.h"
#include "velmiskinnm.h"
#include "vecherskymp.h"
#include "vidyaykinia.h"
#include "gladyshevadn.h"
#include "guskovaim.h"
#include "dudorovdv.h"
#include "zavaryuhinayuv.h"
#include "inshakovaas.h"
#include "katinda.h"
#include "kulaginpa.h"
#include "maksimovso.h"
#include "nikulovia.h"
#include "osipovda.h"
#include "parshindi.h"
#include "potapkinayuyu.h"
#include "rodkinada.h"
#include "ruzaevaas.h"
#include "svetilnikovdb.h"
#include "taynovaa.h"
#include "tepaykinma.h"
#include "utkinnv.h"
#include "chernovaaa.h"
#include "shabanovdo.h"
#include "zhalninrv.h"


void print_usage(char* name);


int main(int argc, char** argv)
{
  if (argc < 3) {
    print_usage(argv[0]);
    return 0;
  }

  lab *l = NULL;
  if (strcmp(argv[1], "zhalninrv") == 0) {
    l = new zhalninrv();
  }
  else if (strcmp(argv[1], "akishevdv") == 0) {
    l = new akishevdv();
  }
  else if (strcmp(argv[1], "velmiskinnm") == 0) {
    l = new velmiskinnm();
  }
  else if (strcmp(argv[1], "vecherskymp") == 0) {
    l = new vecherskymp();
  }
  else if (strcmp(argv[1], "vidyaykinia") == 0) {
    l = new vidyaykinia();
  }
  else if (strcmp(argv[1], "gladyshevadn") == 0) {
   l = new gladyshevadn();
  }
  else if (strcmp(argv[1], "guskovaim") == 0) {
    l = new guskovaim();
  }
  else if (strcmp(argv[1], "dudorovdv") == 0) {
    l = new dudorovdv();
  }
  else if (strcmp(argv[1], "zavaryuhinayuv") == 0) {
   l = new zavaryuhinayuv();
  }
  else if (strcmp(argv[1], "inshakovaas") == 0) {
    l = new inshakovaas();
  }
  else if (strcmp(argv[1], "katinda") == 0) {
    l = new katinda();
  }
  else if (strcmp(argv[1], "kulaginpa") == 0) {
    l = new kulaginpa();
  }
  else if (strcmp(argv[1], "maksimovso") == 0) {
    l = new maksimovso();
  }
  else if (strcmp(argv[1], "nikulovia") == 0) {
    l = new nikulovia();
  }
  else if (strcmp(argv[1], "osipovda") == 0) {
    l = new osipovda();
  }
  else if (strcmp(argv[1], "parshindi") == 0) {
    l = new parshindi();
  }
  else if (strcmp(argv[1], "potapkinayuyu") == 0) {
    l = new potapkinayuyu();
  }
  else if (strcmp(argv[1], "rodkinada") == 0) {
    l = new rodkinada();
  }
  else if (strcmp(argv[1], "ruzaevaas") == 0) {
    l = new ruzaevaas();
  }
  else if (strcmp(argv[1], "svetilnikovdb") == 0) {
    l = new svetilnikovdb();
  }
  else if (strcmp(argv[1], "taynovaa") == 0) {
    l = new taynovaa();
  }
  else if (strcmp(argv[1], "tepaykinma") == 0) {
    l = new tepaykinma();
  }
  else if (strcmp(argv[1], "utkinnv") == 0) {
    l = new utkinnv();
  }
  else if (strcmp(argv[1], "chernovaaa") == 0) {
    l = new chernovaaa();
  }
  else if (strcmp(argv[1], "shabanovdo") == 0) {
    l = new shabanovdo();
  }
  else  {
    print_usage(argv[0]);
    return 0;
  }

  l->read_file();
  l->run(atoi(argv[2]));
  l->write_result();
  l->check_result();

  //delete l; // TODO:
  return 0;
}


void print_usage(char* name)
{
  std::cout << "Usage:\n\n  " << name << " <fio> <lab_number>\n";
}
