# sudo apt install musl-tools

c_compiler=/usr/bin/musl-gcc

CFLAGS="-std=c99 -static -D_POSIX_SOURCE"

mkdir -p dist/

$c_compiler $CFLAGS -o dist/main.run main.c

echo "./dist/main.run"
./dist/main.run