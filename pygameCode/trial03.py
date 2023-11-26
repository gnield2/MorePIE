import pygame

pygame.init()

width = 800
height = 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Main Menu")

while True:
	# Event handler
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			pygame.quit()

	
pygame.quit()
