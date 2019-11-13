cd bin
time g++ -I../include           \
         -m32                   \
         ../src/*.cpp           \
         -c -s -std=c++17 -O3
rm -f bin/a.out
