# sudo apt install musl-tools

c_compiler=/usr/bin/musl-gcc

CFLAGS="-std=c99 -static -D_POSIX_SOURCE"

mkdir -p dist/

$c_compiler $CFLAGS -o dist/test.run _test.c

echo "./dist/test.run"
./dist/test.run