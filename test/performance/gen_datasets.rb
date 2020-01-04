#!/usr/bin/env ruby

to_create = ARGV[0].strip.to_i

groups_name_template = %w(
  Andromeda Antlia Apus Aquarius Aquila Ara Aries Auriga Boötes Caelum Camelopardalis Cancer
  Canes\ Venatici Canis\ Major Canis\ Minor Capricornus Carina Cassiopeia Centaurus Cepheus Cetus
  Chamaeleon Circinus Columba Coma\ Berenices Corona\ Australis Corona\ Borealis Corvus Crater Crux Cygnus
  Delphinus Dorado Draco Equuleus Eridanus Fornax Gemini Grus Hercules Horologium Hydra Hydrus Indus Lacerta
  Leo Leo\ Minor Lepus Libra Lupus Lynx Lyra Mensa Microscopium Monoceros Musca Norma Octans Ophiuchus Orion
  Pavo Pegasus Perseus Phoenix Pictor Pisces Piscis\ Austrinus Puppis Pyxis Reticulum Sagitta Sagittarius Scorpius
  Sculptor Scutum Serpens Sextans Taurus Telescopium Triangulum Triangulum\ Australe Tucana Ursa\ Major Ursa\ Minor
  Vela Virgo Volans Vulpecula
)
group_template = "INSERT INTO groups (id, name) VALUES (':gid', ':name');"
user_template = "INSERT INTO users (id, username, gid, homedir) VALUES (':uid', ':username', ':gid', '/home/:username');"

start_uid = 10000
start_gid = 10000

groups = (1..to_create).reduce([]) do |acc, i|
  acc << ({ id: start_gid + i, name: "#{groups_name_template.sample} #{start_gid + i}"})
end

group_queries = groups.map { |group| group_template.gsub(':gid', group[:id].to_s).gsub(':name', group[:name]) }

group_queries.each_slice(100) do |batch|
  `echo "#{batch.join(" ")}" | sudo mysql -u root sos-sso-production`
end

users = (1..to_create).reduce([]) do |acc, i|
  acc << ({ id: start_uid + i, name: "#{groups_name_template.sample} #{start_uid + i}"})
end

users_queries = users.map do |user|
  user_template
    .gsub(':uid', user[:id].to_s)
    .gsub(':username', user[:name])
    .gsub(':gid', groups.sample[:id].to_s)
end

users_queries.each_slice(500) do |batch|
  `echo "#{batch.join(" ")}" | sudo mysql -u root sos-sso-production`
end
