# piControlBot | Commands

This file contains all the bot commands with their descriptions.

## start

This command is used only once and is used to register your id in the bot.
The id is used to send the summary every hour and to verify the identity of the admin to use important commands.

## temperature
It is used to see the CPU temperature of your raspberry.

It could be used in case the Raspberry is used 24 hours a day to be sure that the processor is not overheated.

## restart
This command restarts the Raspberry using:
```bash
sudo shutdown now -r
```

## shutdown
This command turns off the Raspberry using:
```bash
sudo shutdown now
```

## speedtest
This command checks the speed of the internet using speedtest-cli.

You need to install it:
```bash
sudo pip3 install speedtest-cli
```

## upgrade
This command updates the system using:
```bash
sudo apt-get upgrade
```