INSERT INTO groups (id, name) VALUES ('9000', 'immortals');
INSERT INTO users (
  id, username, gid, gecos, homedir, shell, password, 
  lstchg, min, max, warn, inact, expire, flag
)
  VALUES (
    '8000', 'katarina', '9000', 'Katarina Freya,501,,,,', '/home/katarina', '/bin/bash', 'xxx*hashed_password*xxx',
    2, 5, 1000, 67, 10, 4004, 1
  );
INSERT INTO groups_users (group_id, user_id) VALUES ('9000', '8000');
