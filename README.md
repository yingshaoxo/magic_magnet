# magic_magnet
A torrent client that implements yingshaoxo torrent protocol.


## Yingshaoxo Torrent Protocol

1. For all those clients, it will need at least one tracker service. That service has an public ip address. It only need to have one open port.

2. When a client open a new torrent, I mean seeding. That client will do a report to the tracker with the following infomation: {"has_public_ip": "*.*.*.*", "hash": "", "size": 100}

3. When a client want to download a file with certain hash from a magnet link, it will do a asking to the tracker. If the tracker found there has a resource that matchs the hash code, if the seeder has public ip address, then it will let the client do a download directly from that seeder, otherwise, if that seeder does not have an public ip address, then the tracker will ask the seeder to upload its resources first, then transfer it to the client that asks the resources.
