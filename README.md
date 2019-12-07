# Target machine
- Satellite Gen. B
    - Hardware:
        - Raspberry Pi Zero W
        - MPU9250
        - 3 Hbridges and custom magnetorquers (for every axis)
    - Operating System: `Raspbian Lite (Linux)`
    - Libraries (forked):
        - https://github.com/Rogozin-high-school/WiringPi
        - https://github.com/Rogozin-high-school/CrossPlatformDataBus
        - https://github.com/Rogozin-high-school/MPU

# Building Satellite Gen. B  
It is very (very) recommended to compile on the lab's beefy computer.  
Note that Satellite Gen. B's processor architecture is ARMv6 so you need to work a bit harder.  
1. First of all, download the libraries and compile them (if not compiled yet).  
   Run `scripts/gen_b/build_libraries.sh`.  
2. Determine the satellite's IP (we have yet to find a good automated way for this).  
   Run `scripts/gen_b/set_ip.sh`, followed by the satellite's IP.  
   For example: `./scripts/gen_b/set_ip.sh 10.17.110.165`.  
3. Run `scripts/gen_b/build.sh` and wait.  
4. Run `scripts/gen_b/run.sh`.  

# Properties  
See file `properties`.  
These will be the properties that will be loaded to the satellite by default.  
They can be changed at run-time by the ground station.  

# Fixing VS Code Workspace Settings  
Run `python3 scripts/fix_vscode_workspace.py`.  
