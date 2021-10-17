INSERT INTO `groups` (gid, password, name) VALUES ('9000', 'xxx*group_hashed_password*xxx', 'immortals');
INSERT INTO `users` (
  uid, username, gid, gecos, homedir, shell, password,
  lstchg, min, max, warn, inact, expire, flag
)
  VALUES (
    '8000', 'katarina', '9000', 'Katarina Freya,501,,,,', '/home/katarina', '/bin/bash', 'xxx*hashed_password*xxx',
    2, 5, 1000, 67, 10, 4004, 1
  );
INSERT INTO `grouplist` (gid, username) VALUES ('9000', 'katarina');


INSERT INTO `groups` (gid, name) VALUES ('9001', 'final fantasy 15');
INSERT INTO `users` (uid, username, gid, homedir, shell, max, warn) VALUES ('8001', 'noctis', '9001', '/home/noctis', '/usr/bin/rssh', '9999', '30');
INSERT INTO `grouplist` (gid, username) VALUES ('9001', 'noctis');
INSERT INTO `users` (uid, username, gid, homedir, shell, max, warn) VALUES ('8002', 'cindy', '9001', '/home/cindy', '/usr/bin/rssh', '9999', '30');
INSERT INTO `grouplist` (gid, username) VALUES ('9001', 'cindy');

INSERT INTO `groups` (gid, name) VALUES ('9002', 'final fantasy 7');
INSERT INTO `users` (uid, username, gid, homedir, shell, max, warn) VALUES ('8003', 'cloud', '9002', '/home/cloud', '/usr/bin/rssh', '9999', '30');
INSERT INTO `grouplist` (gid, username) VALUES ('9002', 'cloud');

INSERT INTO `users` (uid, username, gid, homedir, shell, max, warn) VALUES ('8004', 'chocobo', '9002', '/home/chocobo', '/usr/bin/rssh', '9999', '30');
INSERT INTO `grouplist` (gid, username) VALUES ('9001', 'chocobo');
INSERT INTO `grouplist` (gid, username) VALUES ('9002', 'chocobo');

INSERT INTO `users` (uid, username, gid, gecos, homedir, shell) VALUES ('8005', 'testutf', '9000', 'Činčila číha na vĺča,501,,,,', '/home/testutf', '/usr/bin/rssh');
INSERT INTO `grouplist` (gid, username) VALUES ('9000', 'testutf');
