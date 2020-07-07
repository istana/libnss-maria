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
      $SUDO_COMMAND mysql -u root sos-sso-production
      cat /home/libnss-maria/test/fixtures/lots_of_group_members.sql | \
      $SUDO_COMMAND mysql -u root sos-sso-production
      cat /home/libnss-maria/test/fixtures/long_data.sql | \
      $SUDO_COMMAND mysql -u root sos-sso-production
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
      mysql $SSL_COMMAND -uroot -ptoor -hdatabase sos-sso-production
      cat /home/libnss-maria/test/fixtures/lots_of_group_members.sql | \
      mysql $SSL_COMMAND -uroot -ptoor -hdatabase sos-sso-production
      cat /home/libnss-maria/test/fixtures/long_data.sql | \
      mysql $SSL_COMMAND -uroot -ptoor -hdatabase sos-sso-production
    fi
  fi
}

## passwd
@test "finds known user passwd entry by name" {
  run getent passwd johnsilver_shoozee9shaequ2gi2beechoof3Nuxio4hee7geiDaqu7aezaiyee9aebai6xieF3uez2Oriec3quohjie2Shoh6aiZah7EebohGh0ji8ui6aefoquu3shu9ay0Tee7oakej7the1Aishe0ci8chee5iY3eC9aej1Weuliequai0Nahd3viemaiYeedaehishei0meixiejahghaeCh7Igeijeithohquia8johl8Siechfhfhfh
  [[ $status -eq 0 ]]
  [[ $output == *"johnsilver"* ]]
}

@test "finds known user passwd entry by ID" {
  run getent passwd 1234567890
  [[ $status -eq 0 ]]
  [[ $output == *"johnsilver"* ]]
}

@test "finds all user passwd entries" {
  run getent passwd
  [[ "$status" -eq 0 ]]
  [[ "$output" == *"johnsilver"* ]]
}

## shadow
@test "finds known user shadow entry by name" {
  run $SUDO_COMMAND getent shadow johnsilver_shoozee9shaequ2gi2beechoof3Nuxio4hee7geiDaqu7aezaiyee9aebai6xieF3uez2Oriec3quohjie2Shoh6aiZah7EebohGh0ji8ui6aefoquu3shu9ay0Tee7oakej7the1Aishe0ci8chee5iY3eC9aej1Weuliequai0Nahd3viemaiYeedaehishei0meixiejahghaeCh7Igeijeithohquia8johl8Siechfhfhfh
  [[ $status -eq 0 ]]
  [[ $output == *"johnsilver"* ]]
}

@test "finds all user shadow entries" {
  run $SUDO_COMMAND getent shadow
  [[ "$status" -eq 0 ]]
  [[ "$output" == *"johnsilver"* ]]
}

## group
@test "finds all users belonging to a group, primary and secondary members" {
  run getent group management
  [[ $status -eq 0 ]]
  [[ $output == *"management:x:10000:user001,user002,user003,user004,user005,user006,user007,user008,user009,user010,user011,user012,user013,user014,user015,user016,user017,\
user018,user019,user020,user021,user022,user023,user024,user025,user026,user027,user028,user029,user030,user031,user032,user033,user034,user035,user036,user037,user038,user039,\
user040,user041,user042,user043,user044,user045,user046,user047,user048,user049,user050,user051,user052,user053,user054,user055,user056,user057,user058,user059,user060,user061,\
user062,user063,user064,user065,user066,user067,user068,user069,user070,user071,user072,user073,user074,user075,user076,user077,user078,user079,user080,user081,user082,user083,\
user084,user085,user086,user087,user088,user089,user090,user091,user092,user093,user094,user095,user096,user097,user098,user099,user100,user101,user102,user103,user104,user105,\
user106,user107,user108"* ]]

  run getent group 10000
  [[ $status -eq 0 ]]
  [[ $output == *"management:x:10000:user001,user002,user003,user004,user005,user006,user007,user008,user009,user010,user011,user012,user013,user014,user015,user016,user017,\
user018,user019,user020,user021,user022,user023,user024,user025,user026,user027,user028,user029,user030,user031,user032,user033,user034,user035,user036,user037,user038,user039,\
user040,user041,user042,user043,user044,user045,user046,user047,user048,user049,user050,user051,user052,user053,user054,user055,user056,user057,user058,user059,user060,user061,\
user062,user063,user064,user065,user066,user067,user068,user069,user070,user071,user072,user073,user074,user075,user076,user077,user078,user079,user080,user081,user082,user083,\
user084,user085,user086,user087,user088,user089,user090,user091,user092,user093,user094,user095,user096,user097,user098,user099,user100,user101,user102,user103,user104,user105,\
user106,user107,user108"* ]]
}

@test "finds all groups a user belongs to" {
  run groups user001
  [[ "$status" -eq 0 ]]
  [[ "$output" == *"management"* ]]
}

@test "finds all groups entries" {
  run getent group
  [[ "$status" -eq 0 ]]
  [[ "$output" == *"management:x:10000:user001,user002,user003,user004,user005,user006,user007,user008,user009,user010,user011,user012,user013,user014,user015,user016,user017,\
user018,user019,user020,user021,user022,user023,user024,user025,user026,user027,user028,user029,user030,user031,user032,user033,user034,user035,user036,user037,user038,user039,\
user040,user041,user042,user043,user044,user045,user046,user047,user048,user049,user050,user051,user052,user053,user054,user055,user056,user057,user058,user059,user060,user061,\
user062,user063,user064,user065,user066,user067,user068,user069,user070,user071,user072,user073,user074,user075,user076,user077,user078,user079,user080,user081,user082,user083,\
user084,user085,user086,user087,user088,user089,user090,user091,user092,user093,user094,user095,user096,user097,user098,user099,user100,user101,user102,user103,user104,user105,\
user106,user107,user108"* ]]
}
