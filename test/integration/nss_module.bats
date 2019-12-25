#!/usr/bin/env bats

setup() {
  if [[ "$BATS_TEST_NUMBER" -eq 1 ]]; then
    cat /home/libnss-maria/examples/sos-sso/sql/1-db-and-users.sql | \
    sudo mysql -u root &&
    cat /home/libnss-maria/examples/sos-sso/sql/2-data-structures.sql | \
    sudo mysql -u root sos-sso-production &&
    cat /home/libnss-maria/examples/sos-sso/sql/3-privileges.sql | \
    sudo mysql -u root sos-sso-production &&
    cat /home/libnss-maria/examples/sos-sso/sql/4-data.sql | \
    sudo mysql -u root sos-sso-production
  fi
}

## passwd
@test "finds root in passwd database" {
  run getent passwd root
  [[ $status -eq 0 ]]
  [[ $output == "root:x:0:0:root:/root:/bin/bash" ]]
}

@test "finds known user in passwd database by name" {
  run getent passwd katarina
  [[ $status -eq 0 ]]
  [[ $output == *"katarina:x:8000:9000:Katarina Freya,501,,,,:/home/katarina:/bin/bash"* ]]
}

@test "doesn't find unknown user in passwd database by name" {
  run getent passwd eliza
  [[ "$status" -gt 0 ]]
  [[ "$output" == *"no result found"* ]]
}

@test "finds known user in passwd database by id" {
  run getent passwd 8000
  [[ $status -eq 0 ]]
  [[ $output == *"katarina:x:8000:9000:Katarina Freya,501,,,,:/home/katarina:/bin/bash"* ]]
}

@test "doesn't find unknown user in passwd database by id" {
  run getent passwd 8020
  [[ "$status" -gt 0 ]]
  [[ "$output" == *"no result found"* ]]
}

## shadow

@test "finds known user in shadow database by name" {
  run getent shadow katarina
  [[ $status -eq 0 ]]
  echo $output > /dev/stderr
  [[ $output == *"katarina:xxx*hashed_password*xxx:2:5:1000:67:10:4004:1"* ]]
}

@test "doesn't find unknown user in shadow database by name" {
  run getent shadow eliza
  [[ "$status" -gt 0 ]]
  [[ "$output" == *"no result found"* ]]
}

## groups
## TODO: members of the group

@test "finds known group in group database by name" {
  run getent group immortals
  [[ $status -eq 0 ]]
  [[ $output == *"immortals:x:9000:katarina"* ]]
}

@test "doesn't find unknown group in group database by name" {
  run getent group gods
  [[ "$status" -gt 0 ]]
  [[ "$output" == *"_nss_maria_getgrnam_r no result found"* ]]
}

@test "finds known group in group database by id" {
  run getent group 9000
  [[ $status -eq 0 ]]
  [[ $output == *"immortals:x:9000:katarina"* ]]
}

@test "doesn't find unknown group in group database by id" {
  run getent group 9025
  [[ "$status" -gt 0 ]]
  [[ "$output" == *"_nss_maria_getgrgid_r no result found"* ]]
}

@test "returns all users belonging to a group, primary and secondary mambers" {
  run getent group 'final fantasy 15'
  [[ $status -eq 0 ]]
  [[ $output == *"final fantasy 15:x:9001:noctis,cindy,cochobo"* ]]

  run getent group 9001
  [[ $status -eq 0 ]]
  [[ $output == *"final fantasy 15:x:9001:noctis,cindy,cochobo"* ]]
}
