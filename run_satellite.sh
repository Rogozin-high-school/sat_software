printf "Satellite ID: "

read id

sshpass -p "raspberry" \
ssh -t pi@10.17.110.$id "cd ~/sat_software_cpp/bin_satellite && sudo ./a.out"
