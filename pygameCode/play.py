import ctypes
import os
import sys
import pygame
import pygame_menu

NES_SCREEN_WIDTH = 256
NES_SCREEN_HEIGHT = 240

try:
    lib = ctypes.CDLL('lib/libadd.so')
    print("Shared library loaded successfully")
except OSError as e:
    print(f"Error loading the shared library: {e}")

lib.main.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_char_p)]
lib.main.restype = ctypes.c_int

def play_NES(argc, argv, filename):
    window = pygame.display.set_mode((NES_SCREEN_WIDTH, NES_SCREEN_HEIGHT))
    name_of_the_game, extension = os.path.splitext(filename)
    pygame.display.set_caption(name_of_the_game)

    with open(filename, 'rb') as file:
        game_data = file.read()
    
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
                    pygame.quit()
                    sys.exit()

        window.fill((0,0,255))
        pygame.display.update()