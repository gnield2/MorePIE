import pygame
pygame.init()

running = True
screen  = pygame.display.set_mode((800,600), pygame.SCALED)
pygame.display.set_caption("Main Menu")

while running:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			running = False
		screen.fill("grey")
		pygame.display.flip()
	

pygame.quit()
