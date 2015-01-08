Spark Cue Light Project
----

#### Dependencies

- spark-cli
- dfu-util
> Flashing from the spark-cli requires dfu-util, availible at
> http://dfu-util.sourceforge.net/releases/dfu-util-0.8-binaries/linux-i386/

#### compiling

`spark compile cuelight.cpp HttpClient.cpp HttpClient.h --saveTo firmware.bin`  

#### flashing

- hold **reset** and **mode** buttons
- release **reset**
- release **mode** when the led indicator flashes yellow.
- flash the compiled firmware with `sudo spark flash --usb firmware.bin`
