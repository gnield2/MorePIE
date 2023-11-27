import os
import pygame
import pygame_menu

width, height = 1024, 600
white = (255, 255, 255)
black = (0, 0, 0)

def show_selectDir_screen(screen):
	menu = pygame_menu.Menu('Choose Your ROMS Directory', width, height, theme=pygame_menu.themes.THEME_BLUE)
	displayRoms(screen, menu)
	menu.mainloop(screen)

def displayRoms(screen, menu):
	screen.fill(white)
	menu.clear()
	currdir = os.getcwd()
	romsdir = f'{currdir}' + '/roms'
	roms = [d for d in os.listdir(romsdir)]

	for rom in roms:
		menu.add.button(rom, None, os.path.join(romsdir, rom))

def window():

	pygame.init()

	screen = pygame.display.set_mode((width, height))
	clock = pygame.time.Clock()
	menu = pygame_menu.Menu('MoRePIE', width, height, theme=pygame_menu.themes.THEME_BLUE)

	pygame.display.set_caption("MoRePIE")
	menu.add.button("Press Enter to Continue", None)

	current_screen = "startup"

	running = True
	while running:
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				running = False
			elif event.type == pygame.KEYDOWN:
				if event.key == pygame.K_ESCAPE:
					running = False
				if current_screen == "startup" and event.key == pygame.K_RETURN:
					current_screen = "selectDir"

        # Update logic here

		screen.fill(white)

		if current_screen == "selectDir":
			show_selectDir_screen(screen)

		menu.update(pygame.event.get())
		menu.draw(screen)

		pygame.display.flip()
		clock.tick(60)

	pygame.quit()

if __name__ == "__main__":
	window()
