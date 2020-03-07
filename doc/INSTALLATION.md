# piControlBot | Installation

This tutorial will guide you through the installation of piControlBot.

It's done on Raspbian, you can try on other Linux distributions but correct functioning is not guaranteed.

## Dependencies

First of all you need to install the dependencies:

```bash
sudo apt-get install python3-pip & sudo pip3 install speedtest-cli
```

## tgbot-cpp

Then you need to install tgbot-cpp.

```bash
sudo apt-get install g++ make binutils cmake libssl-dev libboost-system-dev zlib1g-dev
```

```bash
git clone https://github.com/reo7sp/tgbot-cpp
cd tgbot-cpp
cmake .
make -j4
sudo make install
```

## piControlBot

After doing all of this we can install the bot itself.

```bash
git clone https://github.com/JMax45/piControlBot
```
Go to the directory:

```bash
cd piControlBot
```

Compile the bot with the following command:

```bash
./compile.sh
```

If all went well, the bot can be used.

If, however, there are errors, it means that you have made a mistake before or are using an operating system that requires a different installation.

If you are using Raspbian, try repeating the steps above, if errors still occur you can open an issue [here](https://github.com/JMax45/piControlBot/issues) and i will try to help you.

## Usage

If the compilation was successful, you can start the bot with the following command:

```bash
./piControlBot
```

A token will be requested, you can get one from [@BotFather](https://telegram.me/BotFather).

After inserting the token you will have to write /start to the bot that you have registered on @BotFather and your id will be saved.

If you got this far, the bot has been successfully configured and can be used.