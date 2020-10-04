INSERT INTO groups (id, password, name) VALUES ('9000', 'xxx*group_hashed_password*xxx', 'immortals');
INSERT INTO users (
  id, username, gid, gecos, homedir, shell, password,
  lstchg, min, max, warn, inact, expire, flag
)
  VALUES (
    '8000', 'katarina', '9000', 'Katarina Freya,501,,,,', '/home/katarina', '/bin/bash', 'xxx*hashed_password*xxx',
    2, 5, 1000, 67, 10, 4004, 1
  );
INSERT INTO groups_users (group_id, user_id) VALUES ('9000', '8000');


INSERT INTO groups (id, name) VALUES ('9001', 'final fantasy 15');
INSERT INTO users (id, username, gid, homedir) VALUES ('8001', 'noctis', '9001', '/home/noctis');
INSERT INTO groups_users (group_id, user_id) VALUES ('9001', '8001');
INSERT INTO users (id, username, gid, homedir) VALUES ('8002', 'cindy', '9001', '/home/cindy');
INSERT INTO groups_users (group_id, user_id) VALUES ('9001', '8002');

INSERT INTO groups (id, name) VALUES ('9002', 'final fantasy 7');
INSERT INTO users (id, username, gid, homedir) VALUES ('8003', 'cloud', '9002', '/home/cloud');
INSERT INTO groups_users (group_id, user_id) VALUES ('9002', '8003');

INSERT INTO users (id, username, gid, homedir) VALUES ('8004', 'chocobo', '9002', '/home/chocobo');
INSERT INTO groups_users (group_id, user_id) VALUES ('9001', '8004');
INSERT INTO groups_users (group_id, user_id) VALUES ('9002', '8004');

INSERT INTO users (id, username, gid, gecos, homedir) VALUES ('8005', 'testutf', '9000', 'Činčila číha na vĺča,501,,,,', '/home/testutf');
INSERT INTO groups_users (group_id, user_id) VALUES ('9000', '8005');
