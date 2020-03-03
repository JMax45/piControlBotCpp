# piControlBot

piControlBot is a bot that helps you check the status of your raspberry pi through [Telegram](https://telegram.org/).

This allows you to stay in touch with your raspberry even from your phone.

The bot contains a list of commands that will be expanded, for example you can get the IP of your raspberry or check the CPU temperature.

In addition, every hour the bot sends a summary of the raspberry status to the admin.

All tests are performed on [Raspbian](https://www.raspberrypi.org/downloads/raspbian/), for now I cannot guarantee stable performance on other linux distributions.

## Installation

Use git to clone piControlBot:

```bash
git clone https://github.com/JMax45/piControlBot
```

## Usage

Use _./compile.sh_ to compile:
```bash
./compile.sh
```
Launch the bot:
```bash
./piControlBot
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)
