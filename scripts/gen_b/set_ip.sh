home=$(dirname "$0")/../..

cd $home
rm -f gen_b.ip
printf $1 > gen_b.ip
