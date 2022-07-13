# Generator of SSH configuration file

Generator of SSH configuration file is an application which allows you to create output config file based on input json file with decribed:

- Targets
- Gateways
- Which gateway should be used to connect to specified target
- Proxy Command

## Features

- Configure json file according to your needs
- Save configuration file in .txt format 
#

## 1. Installation ⚙🛠
### Clone the repository

```sh
git clone https://github.com/nataliaskupien/Generate-ssh-configuration
```
### Install submodule
This project include library from another repository. To install and use submodule, first, you need to initialize the submodule:
```sh
git submodule init
```
Then you need to run the update in order to pull down the files:
```sh
git submodule update
```
At the end install library with:
```sh
sudo apt-get install nlohmann-json3-dev
```
### Install GoogleTest

If you want to use this project wiht unit test included in folder tests, you have to install gtest. Follow commands as shown below:

```sh
sudo apt-get install libgtest-dev
```

```sh
sudo apt-get install cmake
```

```sh
cd /usr/src/gtest
```

```sh
sudo cmake CMakeLists.txt
```

```sh
sudo make
```

```sh
sudo cp *.a /usr/lib
```
Note: If this command doesn't work, use instead:

```sh
sudo cp ./lib/libgtest*.a /usr/lib
```
## 2. How to build the project 💻🔨
Open your terminal and write a commands shown below.

First you have to be in the folder where you saved this project. Use:

```sh
cd "folder_name"
```

Next you have to compile the program with CMake. First you have to create build folder. Use:

```sh
mkdir build
```
Next navigate to the build directory and run CMake to configure the project and generate a native build system. Use:

```sh
cd build
```
Then run cmake and point to the parent directory. Use:

```sh
cmake ..
```
And finally run make to build your project. Use:

```sh
make
```
## 3. Description of .json file 📕

Configure the config.json file depended on your configuration needs. Short introduction of this file: 
### Tragets
```sh
 "targets": {
        "<target_name>": ["<first parameters>",
                          "<second parameters>",]
```
In "targets" you specify your own target with **<target_name>** and with the **parameters** of this target. You can write as much parameters as you need.
### Gateways
```sh
 "gateways": {
        "<gateway_name>": ["<first parameters>",
                          "<second parameters>",]
```
The logic is the same as with **targets**.
### Links
```sh
 "links": {
        "<gateway_name>": ["<target_name>"]
```
In links you specify which gateway should be used to get to a specific target.
### Link Command
```sh
 "linkCommand: "ProxyCommand ssh -W %h:%p <gateway>"
```
That's the command that will be assign to target. The **<gateway>** will be replace automatically with the right **gateway name** which is assign to the target.

## 4. How to run the program 🏃‍♂️

Go to the build directory in folder with project and run command shown below:
```sh
./generate_ssh_config -input "<absolute path to json file>" -output <output file name.txt>
```
You don't have to specify the output file name. In that case the file will be save with default name.

```sh
./generate_ssh_config -input "<absolute path to json file>"
```