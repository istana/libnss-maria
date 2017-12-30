

MYSQL* nss_maria_db_connect(Nssmaria_configuration *settings) {
  MYSQL *mysql_handle = mysql_init(NULL);

  // what to do with this?
  if(!mysql_thread_safe()) { LOG_ERROR("environment is NOT threadsafe!") }
  if(mysql_handle == NULL) { LOG_ERROR("cannot initialize mysql") }

  MYSQL *connection = mysql_real_connect(mysql_handle, settings.dbhost, settings.dbuser,
    settings.dbpass, settings.dbname, atoi(settings.dbport), NULL, 0
  );

  if(connection == NULL) { LOG_MYSQL_ERROR("could not connect to the database", mysql_handle) }

  return connection;
}

void nss_maria_db_cleanup(query, connection) {
  s
}

MYSQL_STMT *statement nss_maria_initialize_statement() {
  MYSQL_STMT *statement = mysql_stmt_init(connection);

  if(statement == NULL) {
    LOG_MYSQL_STATEMENT_ERROR("cannot allocate memory for prepared statement", statement, mysql_handle);
  }

  return statement;
}
