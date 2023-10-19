# sudo apt install musl-tools

c_compiler=/usr/bin/musl-gcc

mkdir -p dist/

$c_compiler -g0 -s -std=c99 -static -D_POSIX_SOURCE -no-pie -o dist/test.run _test.c

echo "./dist/test.run"
./dist/test.run
