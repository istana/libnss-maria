MYSQL_STMT *statement nss_maria_initialize_statement() {
  MYSQL_STMT *statement = mysql_stmt_init(connection);

  if(statement == NULL) {
    LOG_MYSQL_STATEMENT_ERROR("cannot allocate memory for prepared statement", statement, mysql_handle);
  }

  return statement;
}
