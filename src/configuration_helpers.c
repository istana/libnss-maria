void nss_maria_load_setting(config_t libconfig_object, char *destination, const char *selector) {
  // is freed by libconfig
  const char *buffer = malloc(1024 * sizeof(char));

  if(config_lookup_string(&libconfig_object, selector, &buffer) == CONFIG_TRUE) {
    strncpy(destination, buffer, 1023);
  };
}

int nss_maria_populate_config_from_file(char *libconfig_filepath, Nssmaria_configuration *nss_config) {
  FILE* libconfig_stream = fopen(libconfig_filepath, "r");

  if(libconfig_stream != NULL) {
    // parse libconfig file
    config_t libconfig_object;
    config_init(&libconfig_object);

    if(config_read(&libconfig_object, libconfig_stream) == CONFIG_TRUE) {
      printf("ok");

      nss_maria_load_setting(libconfig_object, nss_config->dbhost, "database_settings.host");
      nss_maria_load_setting(libconfig_object, nss_config->dbname, "database_settings.database");
      nss_maria_load_setting(libconfig_object, nss_config->dbuser, "database_settings.username");
      nss_maria_load_setting(libconfig_object, nss_config->dbpass, "database_settings.password");
      nss_maria_load_setting(libconfig_object, nss_config->dbport, "database_settings.port");

      nss_maria_load_setting(libconfig_object, nss_config->getpwnam, "nss_queries.getpwnam");
      nss_maria_load_setting(libconfig_object, nss_config->getpwuid, "nss_queries.getpwuid");
      nss_maria_load_setting(libconfig_object, nss_config->getspnam, "nss_queries.getspnam");
      nss_maria_load_setting(libconfig_object, nss_config->getspent, "nss_queries.getspent");
      nss_maria_load_setting(libconfig_object, nss_config->getgrnam, "nss_queries.getgrnam");
      nss_maria_load_setting(libconfig_object, nss_config->getgrid, "nss_queries.getgrid");
      nss_maria_load_setting(libconfig_object, nss_config->getgrent, "nss_queries.getgrent");
      nss_maria_load_setting(libconfig_object, nss_config->memsbygid, "nss_queries.memsbygid");
      nss_maria_load_setting(libconfig_object, nss_config->gidsbymem, "nss_queries.gidsbymem");

      config_destroy (&libconfig_object);
      return 0;
    } else {
      printf("error found in file %s, message: %s on line: %i",
        libconfig_filepath,
        config_error_text(&libconfig_object),
        config_error_line(&libconfig_object)
      );
      config_destroy(&libconfig_object);
      return 1;
    }
  } else {
    printf("Opening file : Failed\n");
    printf ("Error no is : %d\n", errno);
    printf("Error description is : %s\n", strerror(errno));
    return 1;
  }

  fclose(libconfig_stream);
}
