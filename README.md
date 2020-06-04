# piControlBot

**This version is no longer maintained, you can visit the maintained one [here](https://github.com/JMax45/piControlBot/)**

piControlBot is a bot that helps you check the status of your raspberry pi through [Telegram](https://telegram.org/).

This allows you to stay in touch with your raspberry even from your phone.

The bot contains a list of commands that will be expanded, for example you can get the IP of your raspberry, check the CPU temperature or perform an sms bombing.

You can check all commands [here](https://github.com/JMax45/piControlBot/blob/master/doc/commands.md).

In addition, every hour the bot sends a summary of the raspberry status to the admin.

All tests are performed on [Raspbian](https://www.raspberrypi.org/downloads/raspbian/), for now I cannot guarantee stable performance on other linux distributions.

## Installation

Use git to clone piControlBot:

```bash
git clone https://github.com/JMax45/piControlBot
```
tgbot-cpp is required, the installation guide is [here](https://github.com/reo7sp/tgbot-cpp#library-installation).

## Configuration
Use _./compile.sh_ to compile:
```bash
./compile.sh
```

Launch the bot:
```bash
./piControlBot
```

The bot token will be requested, you can get one from [@BotFather](https://telegram.me/BotFather).

If it is the first time that the bot is launched, you will have to write him /start on Telegram to register your id.

## Usage

Launch the bot:
```bash
./piControlBot
```

You can also visit the [installation guide](https://github.com/JMax45/piControlBot/blob/master/doc/INSTALLATION.md) to see the complete guide.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)
