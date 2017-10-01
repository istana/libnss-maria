// converts a config, i.e. libnnss-maria.conf to database settings
#include <stdio.h>
#include "../configuration/maria_config.h"

int main(int argc, char *argv[]) {
  if(argc == 1) {
    puts("this program extracts database settings from config file and prints them");
    puts("please supply a path to config file");
    return 1;
  }

  Maria_config config = maria_read_config_file(argv[1]);

  printf("%s\n", config.dbname);
  printf("%s\n", config.dbuser);
  printf("%s\n", config.dbpass);
}
