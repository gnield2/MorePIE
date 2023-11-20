import pygame
import pygame_menu

width, height = 1024, 600
white = (255, 255, 255)
black = (0, 0, 0)

def button_click():
	print("Button Clicked!")

def show_new_screen():
	font = pygame_menu.font.FONT_8BIT
	menu = pygame_menu.Menu('Welcome to MoRePIE!', width, height, theme=pygame_menu.themes.THEME_BLUE)
	menu.mainloop(screen)

def window():

	pygame.init()

	screen = pygame.display.set_mode((width, height))
	clock = pygame.time.Clock()
	menu = pygame_menu.Menu('MoRePIE', width, height, theme=pygame_menu.themes.THEME_BLUE)

	pygame.display.set_caption("MoRePIE")
	menu.add.button("Click Me", button_click)

	current_screen = "startup"

	running = True
	while running:
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				running = False
			elif event.type == pygame.KEYDOWN:
				if event.key == pygame.K_ESCAPE:
					running = False
				if current_screen == "startup" and event.type == pygame.K_SPACE:
					current_screen = "new"
			elif event.type == pygame.MOUSEBUTTONDOWN:
				mouse_x, mouse_y = pygame.mouse.get_pos()
				button_click()
				print(mouse_x)
				print(mouse_y)

        # Update logic here

		screen.fill(white)

		if current_screen == "new":
			show_new_screen()

		menu.update(pygame.event.get())
		menu.draw(screen)

		pygame.display.flip()
		clock.tick(60)

	pygame.quit()

if __name__ == "__main__":
	window()
