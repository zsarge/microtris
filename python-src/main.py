# import required module

from playsound import playsound
import serial
import vlc
import os

# go to script dir
abspath = os.path.abspath(__file__)
dname = os.path.dirname(abspath)
os.chdir(dname)

isPlaying = False

with serial.Serial('/dev/ttyUSB0', 9800, timeout=1) as ser:
	player = vlc.Instance()
	media_list = player.media_list_new()
	media_player = player.media_list_player_new()
	media = player.media_new("./sounds/tetris.mp3")
	media_list.add_media(media)
	media_player.set_media_list(media_list)
	media_player.set_playback_mode(vlc.PlaybackMode(1)) # repeat

	# start playing video
	while True:
		match ser.readline().strip():
			case b'':
				pass
			case b'sound:harddrop':
				pass
			case b'music:gamestart':
				print("restaring music")
				if isPlaying:
					media_player.stop()
				media_player.play()
				isPlaying = True
			case b'sound:move':
				playsound('./sounds/move.wav')
			case b'sound:rotate':
				playsound('./sounds/rotate.wav')
			case b'sound:landed':
				playsound('./sounds/landed.wav')
			case b'sound:gameover':
				#  if isPlaying:
					#  media_player.stop()
				playsound('./sounds/gameover.wav')
			case b'sound:clearline':
				playsound('./sounds/clearline.wav')
			case other:
				print(other)

