import pygame
from Rover import Rover

pygame.init()

display_width = 800
display_height = 800

black = (0,0,0)
white = (255,255,255)
red = (200,0,0)
green = (0,200,0)
blue = (0,0,200)
bright_red = (255,0,0)
bright_green = (0,255,0)
bright_blue = (0,0,255)
cyan = (0,255,255)
someColor = (128,128,128)

coords = [(300, 400), (400, 500), (200, 100), (100, 100), (300, 100), (400, 200), (0, 200), (0, 400), (-90, 300)]

roverX = 375
roverY = 750
roverSpeed = 5

rockList = []

goal = pygame.image.load('Goal.png')
rover = pygame.image.load('Rover.png')
rock = pygame.image.load('Rock.png')

#gameDisplay.blit(img,(x,y))

gameDisplay = pygame.display.set_mode((display_width,display_height))
pygame.display.set_caption('Rover Movement')
clock = pygame.time.Clock()

def initRocks():
    for x, y in coords:
        rockList.append(Rock(x, y))

# create bubble around rover 
# check for collisions on all sides
# move accordingly
def fillBackground():
    gameDisplay.fill(white)
    gameDisplay.blit(goal,(200,0))
    fillRocks()

def fillRocks():
    for x, y in coords:
        pygame.draw.rect(gameDisplay, someColor, (x, y, 100, 100))

def quitGame():
    pygame.quit()
    exit()

class Rock:
    def __init__(self, x, y):
        self.x = x
        self.y = y

# Initializes the arena and runs the simulation
def main():
    initRocks()
    rover = Rover(roverX, roverY, roverSpeed, rockList)

    # This loop asks Rover to move once, then redraws the updated arena
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                quitGame()
                break

        if rover.y > 25:
            rover.move()

        fillBackground()
        roverBox = (rover.x, rover.y, 50, 50)
        pygame.draw.rect(gameDisplay, bright_red, roverBox)
        pygame.display.update()
        clock.tick(15)
        
def menu_screen():
    run = True
    #gameDisplay.fill(someColor)

    while run:
        clock.tick(60)
        gameDisplay.fill(white)
        font = pygame.font.SysFont("comicsans", 60)
        text = font.render("Run Simulation", 1, black)
        gameDisplay.blit(text, (100,200))
        pygame.display.update()
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
                quitGame()

            if event.type == pygame.MOUSEBUTTONDOWN:
                run = False
                print("Starting Simulation...")

    main()

menu_screen()
