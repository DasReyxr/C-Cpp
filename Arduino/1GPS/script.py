import serial
import pynmea2
from datetime import datetime

PORT = "/dev/ttyACM0"
BAUDRATE = 9600

ser = serial.Serial(
    PORT,
    BAUDRATE,
    timeout=1
)

print("================================")
print("      NEO-7M GPS MONITOR")
print("================================")
print()

try:

    while True:

        line = ser.readline().decode(
            "ascii",
            errors="replace"
        ).strip()

        if not line.startswith("$"):
            continue

        try:

            msg = pynmea2.parse(line)

            # GGA: Información principal
            if msg.sentence_type == "GGA":

                print("\n---------- GGA ----------")

                print("Hora:", msg.timestamp)

                print("Latitud:", msg.latitude)
                print("Longitud:", msg.longitude)

                print("GPS Quality:", msg.gps_qual)
                print("Satélites:", msg.num_sats)
                print("HDOP:", msg.horizontal_dil)

                if msg.gps_qual == 0:
                    print("Estado: SIN FIX")

                elif msg.gps_qual == 1:
                    print("Estado: GPS FIX")

                elif msg.gps_qual == 2:
                    print("Estado: DGPS FIX")

            # GSV: Satélites visibles
            elif msg.sentence_type == "GSV":

                print("\n---------- GSV ----------")

                print(
                    "Satélites visibles:",
                    msg.num_sv_in_view
                )

                for satellite in msg.data:
                    print(satellite)

        except pynmea2.ParseError:

            print("Error NMEA:", line)

except KeyboardInterrupt:

    print("\nFinalizando...")

finally:

    ser.close()