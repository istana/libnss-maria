INSERT INTO `groups` (id, password, name) VALUES ('9000', 'xxx*group_hashed_password*xxx', 'immortals');
INSERT INTO `users` (
  id, username, gid, gecos, homedir, shell, password,
  lstchg, min, max, warn, inact, expire, flag
)
  VALUES (
    '8000', 'katarina', '9000', 'Katarina Freya,501,,,,', '/home/katarina', '/bin/bash', '$2a$12$p1JGwXPpd22BZKz/ZUZcMOwZlk2SrQVmkiaqkhrvNY9PMXUYqs.4C',
    2, 5, 1000, 67, 10, 4004, 1
  );
INSERT INTO `groups_users` (group_id, user_id) VALUES ('9000', '8000');


INSERT INTO `groups` (id, name) VALUES ('9001', 'final fantasy 15');
INSERT INTO `users` (id, username, gid, homedir, password)
  VALUES ('8001', 'noctis', '9001', '/home/noctis', '$2a$12$7YAfze4UqNTs2CMZf9jL5ukBw6C/JupZAdsMcDSbYCBGh8EGHnexm');
INSERT INTO `groups_users` (group_id, user_id) VALUES ('9001', '8001');

INSERT INTO `users` (id, username, gid, homedir, password)
  VALUES ('8002', 'cindy', '9001', '/home/cindy', '$2a$12$j4wld4W9N1knQ4k422kLaOfetwCwrO5ySK8TnSHH0mB1n8i.CJyCS');
INSERT INTO `groups_users` (group_id, user_id) VALUES ('9001', '8002');


INSERT INTO `groups` (id, name) VALUES ('9002', 'final fantasy 7');
INSERT INTO `users` (id, username, gid, homedir, password)
  VALUES ('8003', 'cloud', '9002', '/home/cloud', '$2a$12$vv1vjjRxsZNLNLC.O.2MYOx9kCeEm0qSp4aGUjpfVU3xqqV1ZyI/6');
INSERT INTO `groups_users` (group_id, user_id) VALUES ('9002', '8003');

INSERT INTO `users` (id, username, gid, homedir, password)
  VALUES ('8004', 'chocobo', '9002', '/home/chocobo', '$2a$12$wHtl83ZP/nkXtqP5mLmiAOR9fl/aStYhQzalCLaf1LW6Rt9MpM/Re');
INSERT INTO `groups_users` (group_id, user_id) VALUES ('9001', '8004');
INSERT INTO `groups_users` (group_id, user_id) VALUES ('9002', '8004');

INSERT INTO `users` (id, username, gid, gecos, homedir, password)
  VALUES ('8005', 'testutf', '9000', 'Činčila číha na vĺča,501,,,,', '/home/testutf', '$2a$12$jeNrQLtjYKAWG0vOTirvueZeHmQcmfMjhK69j92iK6mdgw/ZbZp4.');
INSERT INTO `groups_users` (group_id, user_id) VALUES ('9000', '8005');
