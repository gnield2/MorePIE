import pygame, pygame_menu
pygame.init()
game = pygame.image.load("../roms/Super_Mario_Bros._World.nes")
screen = pygame.display.set_mode((500, 500))
pygame.display.set_caption("Main Menu")
screen.fill("purple")
screen.blit(game, (0, 0))
pygame.display.flip()

while True:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			pygame.quit()

