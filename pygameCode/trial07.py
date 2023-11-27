import pygame, pygame_menu
from typing import Tuple, Any

pygame.init()
screen = pygame.display.set_mode((500,500))
rom    = '/home/pi/MorePIE/roms/snowflake.png'

def set_difficulty(selected: Tuple, value: Any) -> None:
	print(f'Set Difficulty to {selected[0]} ({value})')	
def start_game() -> None:
	global userName
	print(f'{userName.get_value()}, Great work!')
	# Pop water image
	if pygame.image.get_extended() == True:
		pygame.image.load('/home/pi/MorePIE/roms/snowflake.png')
	# Make sound
menu = pygame_menu.Menu(
	height=300,
	theme=pygame_menu.themes.THEME_BLUE,
	title="Main Menu",
	width=400)

userName = menu.add.text_input('Name:  ', default='Yo momma')
menu.add.selector('Difficulty: ',[('Hard', 1), ('Easy', 2)], onchange=set_difficulty)
menu.add.button('Play', start_game)
menu.add.button('Quit', pygame_menu.events.EXIT)

if __name__ == '__main__':
	menu.mainloop(screen)
