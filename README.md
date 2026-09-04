# Wi-Fire 🧨


## Table of Contents

- [Description](#description)
    - [Project](#project)
    - [Repository](#repository)
    - [Technical Details](#technical-details)
- [License](#license)


## Description

### Project
**Wi-Fire** consists of one transmitter unit equipped with an LCD screen and a 4x4 keypad, along with three receiver units, each featuring two firing channels. All units are operated by individual *ATmega328P* microcontrollers and communicate over a one-to-many network of *nRF24L01+PA+LNA* modules.

### Repository
The code in this repository is organized into two directories, namely [*TX*](TX) and [*RX*](RX), which contain the associated code files for the transmitter and the receiver units respectively. Each of these directories is further divided into two subdirectories, which respectively contain the source (`.cpp`) and header (`.h`) files of the project.

### Technical Details
This project was developed using *Visual Studio Code* on `Windows 10`, with the *PlatformIO* extension employed to upload the code to the *ATmega328P* microcontrollers embedded in *Arduino Nano* boards. Since this was intended as a one-off project for personal use, no further documentation (e.g. circuit diagrams) was assembled.


## License

*Wi-Fire* © *2024* by *Alexandros Iliadis* is licensed under the [MIT License](https://choosealicense.com/licenses/mit/).

A short and simple permissive license with conditions only requiring preservation of copyright and license notices. Licensed works, modifications, and larger works may be distributed under different terms and without source code.

See the [`LICENSE.md`](LICENSE.md) file for more details.