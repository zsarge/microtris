# import required module

from playsound import playsound
import serial
import vlc

isPlaying = False

with serial.Serial('/dev/ttyUSB1', 9800, timeout=1) as ser:
	p = vlc.MediaPlayer("./sounds/tetris.mp3")
	while True:
		match ser.readline().strip():
			case b'':
				pass
			case b'sound:harddrop':
				pass
			case b'music:gamestart':
				print("restaring music")
				if isPlaying:
					p.stop()
				p.play()
			case b'sound:move':
				playsound('./sounds/move.wav')
			case b'sound:rotate':
				playsound('./sounds/rotate.wav')
			case b'sound:landed':
				playsound('./sounds/landed.wav')
			case b'sound:gameover':
				playsound('./sounds/gameover.wav')
			case other:
				print(other)

