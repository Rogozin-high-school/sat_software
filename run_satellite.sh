pi="pi@10.17.110.$1"

sshpass -p "raspberry" \
ssh -t $pi "cd ~/sat_software_cpp/bin_satellite && \
            sudo ./a.out"
