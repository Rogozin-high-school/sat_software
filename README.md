# Target machine
- Satellite Gen. B
    - Hardware:
        - Raspberry Pi Zero W
        - MPU9250
        - 3 Hbridges and custom magnetorquers (for every axis)
    - Operating System: `Raspbian Lite (Linux)`
    - Software:
        - `WiringPi`
        - `CrossPlatformDataBus`
        - `sshpass`

# Building
It is very recommended to compile on the lab's beefy computer.  
Note that Satellite Gen. B's processor architecture is ARMv6 so you need to work a bit harder.  
But generally just run `build_gen_b.sh` and it will do the work.  
To run the program, run `run_gen_b.sh`.
