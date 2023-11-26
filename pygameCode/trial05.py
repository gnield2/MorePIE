import pygame

screen = pygame.display.set_mode((500, 500))
pygame.display.set_caption("Main Menu")
mouse = pygame.Vector2(screen.get_width()/2, screen.get_height()/2)
dt = 0

while True:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			pygame.quit()
	

	screen.fill("purple")
	pygame.draw.circle(screen, "red", mouse, 20)
	pygame.display.flip()


pygame.quit()
