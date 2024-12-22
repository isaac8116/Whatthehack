import serial
import time

port = '/dev/tty.usbserial-210'  # Update with your port
baud_rate = 9600
output_file = 'output_log.txt'

def log_serial_data(port, baud_rate, output_file):
    ser = None  # Initialize to None to avoid UnboundLocalError
    
    try:
        ser = serial.Serial(port, baud_rate, timeout=1)
        print(f"Connected to {port} at {baud_rate} baud...")

        with open(output_file, "w") as file:
            while True:
                if ser.in_waiting > 0:
                    data = ser.readline().decode('utf-8').strip()
                    timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
                    log_entry = f"{timestamp}, {data}\n"
                    print(log_entry, end='')
                    file.write(log_entry)
                    file.flush()

    except serial.SerialException as e:
        print(f"Error: {e}")
    except KeyboardInterrupt:
        print("Logging stopped by user.")
    finally:
        if ser and ser.is_open:
            ser.close()
            print("Serial port closed.")

log_serial_data(port, baud_rate, output_file)