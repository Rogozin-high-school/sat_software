echo Enter satellite IP...

read ip

sshpass -p "raspberry" \
ssh -t pi@$ip "cd ~/sat_software_cpp/bin_satellite && sudo ./a.out"
