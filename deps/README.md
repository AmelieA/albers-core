albers-core
===========

WARNING: If you have set up your environment for FCCSW, this package will not compile. Log out and log in again to clean up your environment. 

core albers library 

On lxplus, before compiling or using this package, set up your environment:

    source init.sh

On MacOS, before compiling or using this package, install ROOT and make sure your environment is correctly set to use ROOT and compile programs based on ROOT. Then, set up your environment:

    source init_macos.sh 
    
Compile:

    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=../install ..
    make -j 4 install
    cd ..

Test:

    ./install/bin/albers-write
    ./install/bin/albers-read
    
