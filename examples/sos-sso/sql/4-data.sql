INSERT INTO groups (id, name) VALUES ('9000', 'clan');
INSERT INTO users (id, username, gid, homedir) VALUES ('8000', 'katarina', '9000', '/home/katarina');
INSERT INTO groups_users (group_id, user_id) VALUES ('9000', '8000');
