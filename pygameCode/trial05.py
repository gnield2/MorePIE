import pygame

screen = pygame.display.set_mode((500, 500))
pygame.display.set_caption("Main Menu")

while True:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			pygame.quit()


	screen.fill("purple")
	pygame.display.flip()


pygame.quit()
