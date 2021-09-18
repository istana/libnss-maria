#!/usr/bin/env bats

setup() {
  if [[ "$BATS_TEST_NUMBER" -eq 1 ]]; then
    if [[ -z $PREDEFINED_DB ]]; then
      cat /home/libnss-maria/examples/sos-sso/sql/1-db.sql | \
      $SUDO_COMMAND mysql -u root &&
      cat /home/libnss-maria/examples/sos-sso/sql/2-users.sql | \
      $SUDO_COMMAND mysql -u root &&
      cat /home/libnss-maria/examples/sos-sso/sql/3-data-structures.sql | \
      $SUDO_COMMAND mysql -u root sos-sso-production &&
      cat /home/libnss-maria/examples/sos-sso/sql/4-privileges.sql | \
      $SUDO_COMMAND mysql -u root sos-sso-production &&
      cat /home/libnss-maria/examples/sos-sso/sql/5-data.sql | \
      $SUDO_COMMAND mysql -u root --default-character-set=utf8 sos-sso-production
    else
      cat /home/libnss-maria/examples/sos-sso/sql/1-db.sql | \
      mysql $SSL_COMMAND -uroot -ptoor -hdatabase &&
      cat /home/libnss-maria/examples/sos-sso/sql/2-users.sql | \
      mysql $SSL_COMMAND -uroot -ptoor -hdatabase &&
      cat /home/libnss-maria/examples/sos-sso/sql/3-data-structures.sql | \
      mysql $SSL_COMMAND -uroot -ptoor -hdatabase sos-sso-production &&
      cat /home/libnss-maria/examples/sos-sso/sql/4-privileges.sql | \
      mysql $SSL_COMMAND -uroot -ptoor -hdatabase sos-sso-production &&
      cat /home/libnss-maria/examples/sos-sso/sql/5-data.sql | \
      mysql $SSL_COMMAND -uroot -ptoor -hdatabase --default-character-set=utf8 sos-sso-production
    fi
  fi
}

## passwd
@test "finds known user passwd entry by name" {
  run getent passwd katarina
  [[ $status -eq 0 ]]
  [[ $output == *"katarina:x:8000:9000:Katarina Freya,501,,,,:/home/katarina:/bin/bash"* ]]
}

@test "doesn't find unknown user passwd entry by name" {
  run getent passwd eliza
  [[ "$status" -gt 0 ]]
  [[ "$output" == *"no result found"* || "$output" == "" ]]
}

@test "finds known user passwd entry by ID" {
  run getent passwd 8000
  [[ $status -eq 0 ]]
  [[ $output == *"katarina:x:8000:9000:Katarina Freya,501,,,,:/home/katarina:/bin/bash"* ]]
}

@test "doesn't find unknown user passwd entry by ID" {
  run getent passwd 8020
  [[ "$status" -gt 0 ]]
  [[ "$output" == *"no result found"* || "$output" == "" ]]
}

@test "finds all user passwd entries" {
  run getent passwd
  [[ "$status" -eq 0 ]]
  [[ "$output" == *"katarina:x:8000:9000:Katarina Freya,501,,,,:/home/katarina:/bin/bash"* ]]
  [[ "$output" == *"noctis:x:8001:9001::/home/noctis:/usr/bin/rssh"* ]]
  [[ "$output" == *"cindy:x:8002:9001::/home/cindy:/usr/bin/rssh"* ]]
  [[ "$output" == *"cloud:x:8003:9002::/home/cloud:/usr/bin/rssh"* ]]
  [[ "$output" == *"chocobo:x:8004:9002::/home/chocobo:/usr/bin/rssh"* ]]
}

@test "UTF-8 characters in GECOS" {
  run getent passwd testutf
  [[ "$status" -eq 0 ]]
  [[ "$output" == *"testutf:x:8005:9000:Činčila číha na vĺča,501,,,,:/home/testutf:/usr/bin/rssh"* ]]
}

## shadow
@test "finds known user shadow entry by name" {
  run $SUDO_COMMAND getent shadow katarina
  [[ $status -eq 0 ]]
  [[ $output == *'katarina:$2a$12$p1JGwXPpd22BZKz/ZUZcMOwZlk2SrQVmkiaqkhrvNY9PMXUYqs.4C:2:5:1000:67:10:4004:1'* ]]
}

@test "doesn't find unknown user shadow entry by name" {
  run $SUDO_COMMAND getent shadow eliza
  [[ "$status" -gt 0 ]]
  [[ "$output" == *"no result found"* || "$output" == "" ]]
}

@test "finds all user shadow entries" {
  run $SUDO_COMMAND getent shadow
  [[ "$status" -eq 0 ]]
  [[ "$output" == *'katarina:$2a$12$p1JGwXPpd22BZKz/ZUZcMOwZlk2SrQVmkiaqkhrvNY9PMXUYqs.4C:2:5:1000:67:10:4004:1'* ]]
  [[ "$output" == *'noctis:$2a$12$7YAfze4UqNTs2CMZf9jL5ukBw6C/JupZAdsMcDSbYCBGh8EGHnexm:1:0:9999:30:0::0'* ]]
  [[ "$output" == *'cindy:$2a$12$j4wld4W9N1knQ4k422kLaOfetwCwrO5ySK8TnSHH0mB1n8i.CJyCS:1:0:9999:30:0::0'* ]]
  [[ "$output" == *'cloud:$2a$12$vv1vjjRxsZNLNLC.O.2MYOx9kCeEm0qSp4aGUjpfVU3xqqV1ZyI/6:1:0:9999:30:0::0'* ]]
  [[ "$output" == *'chocobo:$2a$12$wHtl83ZP/nkXtqP5mLmiAOR9fl/aStYhQzalCLaf1LW6Rt9MpM/Re:1:0:9999:30:0::0'* ]]
}

## groups
@test "finds known group in group database by name" {
  run getent group immortals
  [[ $status -eq 0 ]]
  [[ $output == *"immortals:xxx*group_hashed_password*xxx:9000:katarina"* ]]
}

@test "doesn't find unknown group in group database by name" {
  run getent group gods
  [[ "$status" -gt 0 ]]
  [[ "$output" == *"no result found"* || "$output" == "" ]]
}

@test "finds known group in group database by ID" {
  run getent group 9000
  [[ $status -eq 0 ]]
  [[ $output == *"immortals:xxx*group_hashed_password*xxx:9000:katarina"* ]]
}

@test "doesn't find unknown group in group database by ID" {
  run getent group 9025
  [[ "$status" -gt 0 ]]
  [[ "$output" == *"no result found"* || "$output" == "" ]]
}

@test "finds all users belonging to a group, primary and secondary members" {
  run getent group 'final fantasy 15'
  [[ $status -eq 0 ]]
  [[ $output == *"final fantasy 15:x:9001:noctis,cindy,chocobo"* ]]

  run getent group 9001
  [[ $status -eq 0 ]]
  [[ $output == *"final fantasy 15:x:9001:noctis,cindy,chocobo"* ]]
}

@test "finds all groups a user belongs to" {
  run groups chocobo
  [[ "$status" -eq 0 ]]
  [[ "$output" == *"final fantasy 7"* ]]
  [[ "$output" == *"final fantasy 15"* ]]
}

@test "finds all groups entries" {
  run getent group
  [[ "$status" -eq 0 ]]
  [[ "$output" == *"immortals:xxx*group_hashed_password*xxx:9000:katarina"* ]]
  [[ "$output" == *"final fantasy 15:x:9001:noctis,cindy,chocobo"* ]]
  [[ "$output" == *"final fantasy 7:x:9002:cloud,chocobo"* ]]
}
