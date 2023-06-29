# import required module

from playsound import playsound
import serial

with serial.Serial('/dev/ttyUSB0', 9800, timeout=1) as ser:
	while True:
		print(ser.readline())

# for playing note.wav file
#  playsound('/path/note.wav')
#  print('playing sound using  playsound')

