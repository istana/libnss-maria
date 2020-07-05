// converts a config, i.e. libnnss-maria.conf to database settings
#include <stdio.h>
#include "../configuration/maria_config.h"

int main(int argc, char *argv[]) {
  Maria_config *config;

  if(argc == 1) {
    puts("this program extracts database settings from config file and prints them");
    puts("please supply a path to config file");
    return 1;
  }

  config = malloc(sizeof(*config));
  maria_read_config(config, argv[1], argv[2]);

  printf("%s\n", config->dbname);
  printf("%s\n", config->dbuser);
  printf("%s\n", config->dbpass);

  free(config);
  return 0;
}
