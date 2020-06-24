#!/usr/bin/env bats

setup() {
  if [[ "$BATS_TEST_NUMBER" -eq 1 ]]; then
    if [[ -z $DOCKER ]]; then
      cat /home/libnss-maria/examples/sos-sso/sql/1-db.sql | \
      sudo mysql -u root &&
      cat /home/libnss-maria/examples/sos-sso/sql/2-users.sql | \
      sudo mysql -u root &&
      cat /home/libnss-maria/examples/sos-sso/sql/3-data-structures.sql | \
      sudo mysql -u root sos-sso-production &&
      cat /home/libnss-maria/examples/sos-sso/sql/4-privileges.sql | \
      sudo mysql -u root sos-sso-production &&
      cat /home/libnss-maria/examples/sos-sso/sql/5-data.sql | \
      sudo mysql -u root sos-sso-production
    else
      cat /home/libnss-maria/examples/sos-sso/sql/1-db.sql | \
      mysql -unss-maria-user -pIsabelle -hdatabase sos-sso-production &&
      cat /home/libnss-maria/examples/sos-sso/sql/3-data-structures.sql | \
      mysql -unss-maria-user -pIsabelle -hdatabase sos-sso-production &&
      cat /home/libnss-maria/examples/sos-sso/sql/5-data.sql | \
      mysql -unss-maria-user -pIsabelle -hdatabase sos-sso-production
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

## shadow
@test "finds known user shadow entry by name" {
  run getent shadow katarina
  [[ $status -eq 0 ]]
  [[ $output == *"katarina:xxx*hashed_password*xxx:2:5:1000:67:10:4004:1"* ]]
}

@test "doesn't find unknown user shadow entry by name" {
  run getent shadow eliza
  [[ "$status" -gt 0 ]]
  [[ "$output" == *"no result found"* || "$output" == "" ]]
}

@test "finds all user shadow entries" {
  run $SUDO_COMMAND getent shadow
  [[ "$status" -eq 0 ]]
  [[ "$output" == *"katarina:xxx*hashed_password*xxx:2:5:1000:67:10:4004:1"* ]]
  [[ "$output" == *"noctis:x:1:0:9999:30:0::0"* ]]
  [[ "$output" == *"cindy:x:1:0:9999:30:0::0"* ]]
  [[ "$output" == *"cloud:x:1:0:9999:30:0::0"* ]]
  [[ "$output" == *"chocobo:x:1:0:9999:30:0::0"* ]]
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
