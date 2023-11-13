import pygame
import pygame_menu

def button_click():
    print("Button Clicked!")

def window():

    pygame.init()

    width, height = 1024, 600
    white = (255, 255, 255)
    black = (0, 0, 0)

    screen = pygame.display.set_mode((width, height))
    clock = pygame.time.Clock()
    menu = pygame_menu.Menu('MoRePIE', width, height, theme=pygame_menu.themes.THEME_BLUE)

    pygame.display.set_caption("MoRePIE")
    menu.add.button("Click Me", button_click)

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
            elif event.type == pygame.MOUSEBUTTONDOWN:
                mouse_x, mouse_y = pygame.mouse.get_pos()
                print(mouse_x)
                print(mouse_y)

        # Update logic here

        screen.fill(white)

        menu.update(pygame.event.get())
        menu.draw(screen)

        pygame.display.flip()
        clock.tick(60)

    pygame.quit()

if __name__ == "__main__":
    window()
