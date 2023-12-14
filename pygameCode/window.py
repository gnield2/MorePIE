import ctypes
import os
import pygame
import pygame_menu
from play import play_NES

width, height = 800, 600
white = (255, 255, 255)
black = (0, 0, 0)
purple = (128, 0, 128)

def window():

	pygame.init()

	screen = pygame.display.set_mode((width, height))
	clock = pygame.time.Clock()
	menu = pygame_menu.Menu('MoRePIE', width, height, theme=pygame_menu.themes.THEME_BLUE)
	menu.clear()

	pygame.display.set_caption("MoRePIE")

	currdir = os.getcwd()
	romsdir = f'{currdir}' + '/roms'
	roms = [d for d in os.listdir(romsdir)]

	buttons = []
	selected = 0
	for rom in roms:
		button = menu.add.button(rom, None, os.path.join(romsdir, rom))
		buttons.append(button)

	buttons[selected].set_background_color(purple)

	running = True
	while running:
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				running = False
				pygame.quit()
			elif event.type == pygame.KEYDOWN:
				if event.key == pygame.K_ESCAPE:
					running = False
					pygame.quit()
				if event.key == pygame.K_UP:
					buttons[selected].set_background_color(black)
					selected = max(0, selected - 1)
					buttons[selected].set_background_color(purple)
				if event.key == pygame.K_DOWN:
					buttons[selected].set_background_color(black)
					selected = min(len(roms) - 1, selected + 1)
					buttons[selected].set_background_color(purple)
				if event.key == pygame.K_RETURN:
					print("Opening ROM...\n")
					filename = f'{romsdir}' + '/' + f'{roms[selected]}'
					args = [b'6502emulator.c', filename.encode('utf-8')]
					argc = len(args)
					argv = (ctypes.c_char_p * argc)(*args)
					running = False
					play_NES(argc, argv, filename)

        # Update logic here

		screen.fill(white)
		menu.update(pygame.event.get())
		menu.draw(screen)
		pygame.display.flip()
		clock.tick(60)

	pygame.quit()

if __name__ == "__main__":
	window()
