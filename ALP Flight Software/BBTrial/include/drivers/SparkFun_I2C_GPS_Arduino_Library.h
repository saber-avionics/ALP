/*
  This is a library written for the MediaTek MT3333 based GPS module with I2C firmware
  specially loaded. SparkFun sells these at its website: www.sparkfun.com

  Written by Nathan Seidle @ SparkFun Electronics, April 25th, 2017

  This GPS module is special because it can use an I2C interface to communicate.

  This library handles the pulling in of data over I2C. We recommend a parsing engine
  such as TinyGPS.

  https://github.com/sparkfun/SparkFun_I2C_GPS_Arduino_Library

  Do you like this library? Help support SparkFun. Buy a board!

  Development environment specifics:
  Arduino IDE 1.8.1

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
	Modified by Mason Barrow for the Suborbital Atmospheric Balloon
	Elevated Rocket (SABER) project as a part of the Space Hardware
	Club (SHC) at the University of Alabama in Huntsville (UAH).

	November 6 2019
*/

#pragma once

#include <stdint.h>
#include <string>
#include "drivers/I2CDevice.h"

using namespace std;

#define MT333x_ADDR 0x10 //7-bit unshifted default I2C Address

#define MAX_PACKET_SIZE 255
//If packet size is ever more than 255 the head and tail variables will need to be
//changed to something other than uint8_t

#define I2C_SPEED_STANDARD        100000
#define I2C_SPEED_FAST            400000

class I2CGPS {
  public:

    //By default use Wire, standard I2C speed, and the defaul AK9750 address
    bool begin(TwoWire &wirePort = Wire, uint32_t i2cSpeed = I2C_SPEED_STANDARD);

    void check(); //Checks module for new data
    uint8_t available(); //Returns available number of bytes. Will call check() if zero is available.
    uint8_t read(); //Returns the next available byte

    void enableDebugging(Stream &debugPort = Serial); //Output various extra messages to help with debug
    void disableDebugging();

    bool sendMTKpacket(string command);
    string createMTKpacket(uint16_t packetType, string dataField);
    string calcCRCforMTK(string sentence); //XORs all bytes between $ and *

    bool sendPGCMDpacket(string command);
    string createPGCMDpacket(uint16_t packetType, string dataField);
    // Uses MTK CRC

    //Variables
    uint8_t gpsData[MAX_PACKET_SIZE]; //The place to store valid incoming gps data

  private:

    //Variables
    TwoWire *_i2cPort; //The generic connection to user's chosen I2C hardware
    uint8_t _i2caddr;

    bool _printDebug = false; //Flag to print the serial commands we are sending to the Serial port for debug

    Stream *_debugSerial; //The stream to send debug messages to if enabled

    uint8_t _head; //Location of next available spot in the gpsData array. Limited to 255.
    uint8_t _tail; //Location of last spot read from gpsData array. Limited to 255.
};
