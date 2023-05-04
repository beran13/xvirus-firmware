# Dexvmaster0-Firmware

[![Discord](https://img.shields.io/discord/975068703559409685?label=&logo=discord&logoColor=ffffff&color=7389D8&labelColor=6A7EC2)](https://discord.gg/sxrHZbUP6B)

![Show me the code](https://user-images.githubusercontent.com/89728480/209841676-33fb8152-d2ea-4039-a847-c03d1037fa3d.png)

Welcome to [Dexv Zero](https://discord.gg/dexvirus)'s Firmware repo!
My goal is to make a really nice flipper CFW, and to make it a pleasure for everyone to work with.

# Donations: 
**If you like what you're seeing, please consider donating to me. Even tho my fw may not be the best but i had some fun time learning stuff while working on it, but I'd still appreciate a few bucks**

<a href='https://ko-fi.com/N4N7I2HJC' target='_blank'><img height='36' style='border:0px;height:36px;' src='https://storage.ko-fi.com/cdn/brandasset/kofi_button_dark.png' border='0' alt='Buy Me a Coff at ko-fi.com' /></a>

Thanks for all your support <3 | Also check out my [Discord](https://discord.gg/sxrHZbUP6B)

# Build It Yourself

First clone the repository: 
```shell
git clone --recursive https://github.com/DXVVAY/dexvmaster0
```
Then enter the directory:
```shell
cd dexvmaster0
```
Finally build the package for the latest DEV build, be warned bugs may still be found:
```shell
./fbt updater_package
```

# Install Without Compiling

1.Install the latest firmware release from [releases](https://github.com/DXVVAY/Dexvmaster0/releases).

2.Go to qFlipper and connect your Flipper Zero to your PC via USB cable, then click on install from file, when prompted choose the .tgz file.

![image](https://user-images.githubusercontent.com/89728480/209699196-d8eedef0-6fe8-4c80-b151-b52847876466.png)

If this doesn't work then instead:

1.Download the .zip file and extract it into the "updates" folder on your Flipper Zero.

2.Inside your Flipper open the Browser (while on desktop press down then left) and find the updates folder.

3.Open the folder with the name "Dexvmaster0" or something similar and find the file named "update" (it will have an icon of a box with an arrow inside).

4.Select "Run In App"

# Flipper Zero Firmware Breakdown

The Flipper Zero's firmware consists of two components:

- Core2 firmware set - proprietary components by ST: FUS + radio stack. FUS is flashed at factory, and you should never update it.
- Core1 Firmware - HAL + OS + Drivers + Applications.

They must both be flashed in the order described.

# Links

* Discord: [dexvirus/discord](https://discord.gg/sxrHZbUP6B)

# Contact

* DEXV#6969

* ⁀⊙෴☉⁀  Alphax  ⁀⊙෴☉⁀#4657

* Vince#1145


<!-- The machine is now active. Recovery protocol initiated. Please stand by! -->
