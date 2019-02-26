import serial
import sys

def get_serial_ports():
    """
    Lists all available serial ports
    :return a list of all available serial ports
    """
    ports = []
    if sys.platform.startswith('win'):

        for p in ['COM{}'.format(e+1) for e in range(255)]:
            try:
                s=serial.Serial(p)
                s.close()
                ports.append(p)
            except (OSError, serial.SerialException):
                pass
    else:
        raise EnvironmentError('Sorry platform not supported yet')
    return ports

def open_serial_port(serial_port=None, baudrate=9600):
    """
    :return serial Object
    """
    #open the only availyble port and hope its the device you wanted
    if serial_port = None:
        serial_port = get_serial_ports()[0]
    return serial.Serial(port=serial_port, baudrate=baudrate)

if __name__=='__main__':
    print get_serial_ports()
