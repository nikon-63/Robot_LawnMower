import pygame
import sys
import requests
import time


screen = pygame.display.set_mode((540, 540))
pygame.display.set_caption('TEB')

image = pygame.image.load('tractor.jpg')
image = pygame.transform.scale(image, (250, 300))
imageL = pygame.transform.rotate(image, 90)
imageR = pygame.transform.rotate(image, -90)


while True:
    events = pygame.event.get()
    for event in events:
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                screen.fill(0)
                screen.blit(imageL, (145, 120))
                print('Left')
                url = "http://192.168.4.1/Lefton"
                resp = requests.get(url)
                time.sleep(0.1)


            if event.key == pygame.K_RIGHT:
                screen.fill(0)
                screen.blit(imageR, (145, 120))
                print('Right')
                url = "http://192.168.4.1/Righton"
                resp = requests.get(url)
                time.sleep(0.1)


            if event.key == pygame.K_UP:
                screen.fill(0)
                screen.blit(image, (145, 120))
                print('UP')
                url = "http://192.168.4.1/Leftoff"
                resp = requests.get(url)
                time.sleep(0.1)


        pygame.display.update()
