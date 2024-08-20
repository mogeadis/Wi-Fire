# Wi-Fire 🧨


## Table of Contents

- [Description](#description)
    - [Project](#project)
    - [Repository](#repository)
    - [Technical Details](#technical-details)
- [License](#license)


## Description

### Project
**Wi-Fire** consists of one transmitter unit equipped with an LCD screen and a 4x4 keypad, along with three receiver units, each featuring two firing channels. All units are operated by individual ATmega328P microcontrollers embedded in *Arduino Nano* boards and communicate over a one-to-many network of *nRF24L01+PA+LNA* modules.

### Repository
The code in this repository is organized into two directories, namely [TX](TX) and [RX](RX), which contain the associated code files for the transmitter and the receiver units respectively. Each of these directories is further divided into three subdirectories, which separately include the header (`.h`) files, source (`.cpp`) files, and external libraries.

### Technical Details
This project was developed using *Visual Studio Code* on `Windows 10`, with the *PlatformIO* extension employed to upload the code to the *Arduino* boards. Since this was intended as a one-off project for personal use, no further documentation (e.g. circuit diagrams) was assembled.


## License

*Wi-Fire* © *2024* by *Alexandros Iliadis* is licensed under the [GNU General Public License v3.0](https://choosealicense.com/licenses/gpl-3.0/).

Permissions of this strong copyleft license are conditioned on making available complete source code of licensed works and modifications, which include larger works using a licensed work, under the same license. Copyright and license notices must be preserved. Contributors provide an express grant of patent rights.

See the [LICENSE.md](LICENSE.md) file for more details.