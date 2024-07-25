# Desktop

This is a project for building the `Desktop` system which will be launched on `Milk-V DuoS`.

`Milk-V DuoS` is an upgraded model of `Duo`, which has upgraded the `SG2000` controller and has larger memory (`512MB`) and more IO interfaces. It integrates `WI-FI 6`/`BT 5` wireless functionality and is equipped with a USB 2.0 HOST interface and a 100Mbps Ethernet port, making it convenient for users to use. It supports dual cameras (2x MIPI CSI 2-channel) and MIPI video output (MIPI DSI 4-channel), enabling multiple applications. DuoS also supports switching between `RISC-V` and `ARM` startup through a switch. By enhancing performance and interfaces, `DuoS` is more suitable for various scenarios and more complex project development requirements.

The chip also integrates an internal `TPU`, which can provide approximately `0.5 TOPS` of computing power under `INT8` operation. The specially designed `TPU` scheduling engine efficiently provides high bandwidth data streams for tensor processing unit cores. It also provides users with a powerful deep learning model compiler and software SDK development kit. Mainstream deep learning frameworks such as Caffe, Pytorch, ONNX, MXNet, TensorFlow (Lite) can be easily ported to this platform.

## How to build

1. One step compilation using automated scripts

    ```
    cd build
    ./auto.sh
    ```

2. Compile step by step using multiple scripts

    ```
    cd build
    ./clean.sh
    ./build.sh
    ```

    The above operation is equivalent to the first one.

3. Manually using CMake and Make

    > The first method (not recommended due to slow compilation
    speed) :

    ```
    cd build
    cmake .
    make
    ```

    > The second method (recommended, as it utilizes multi-core compilation with CPU) :

    ```
    cd build
    cmake .
    make -jx
    # Please replace 'x' with the number of CPU cores you have.
    ```

## How to run

1. Execute script

    You need to transfer the start.sh script file to DuoS and execute it.

    ```
    ./auto.sh
    ```

2. Execute shell commands

    ```
    insmod /mnt/system/ko/cvi_fb.ko vxres=800 vyres=1280
    insmod /mnt/system/ko/3rd/gt9xx.ko
    nice -n -20 /root/duos-pad/exe
    ```
