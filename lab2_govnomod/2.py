import pygame , sys
import random
from creature import Creature
from fish import Fish
from shark import Shark

FISH = (255,242,100)
SHARK = (73,75,82)
OCEAN = (65,105,225)
BACKGROUND = (62,70,73)
WHITE = (255,255,255)

size = (1000,541)
WIDTH = 90
HEIGHT = 60
CELLSIZE = 8
MARGIN = 1
f = open('C:\\Users\\27les\\Desktop\\lab2_govnomod\\fish.txt', 'w')
s = open('C:\\Users\\27les\\Desktop\\lab2_govnomod\\shark.txt', 'w')

class WORLD:
	global fish_count, shark_count,chronons
	def spawn(self,grid,creature_type):
		spawned = False
		while not spawned:
			x = random.randint(0,HEIGHT-1)
			y = random.randint(0,WIDTH-1)
			if grid[x][y] == 0:
				spawned = True
		if creature_type == "fish":
			grid[x][y] = 1
			fish = Fish(x,y)
		elif creature_type == "shark":
			grid[x][y] = 2
			shark = Shark(x,y)

	def update(self,grid,screen,chronons):
		fish_count = 0
		shark_count = 0
		for y in range(0, HEIGHT):
			for x in range(0,WIDTH):
				if grid[y][x] == 1:
					fish_count+=1
					color = FISH
				elif grid[y][x] == 2:
					shark_count+=1
					color = SHARK
				else:
					color = OCEAN
				pygame.draw.rect(screen,color,
								[(MARGIN + CELLSIZE) * x + MARGIN,
								(MARGIN + CELLSIZE) * y + MARGIN,
								CELLSIZE,CELLSIZE])
		f.write("{ts} {f}\n".format(f=fish_count, ts = chronons))
		s.write("{ts} {s}\n".format(s=shark_count, ts = chronons))
		print(chronons)

	def world_c(self):
		grid = []
		for y in range(0, HEIGHT):
			grid.append([])
			for x in range(0,WIDTH):
				grid[y].append(0)
		return grid


def main():
	global chronons
	chronons = int(1000)
	pygame.init()
	pygame.font.init()
	clock = pygame.time.Clock()
	myfont = pygame.font.SysFont('comicsansms', 15)
	screen = pygame.display.set_mode(size)
	pygame.display.set_caption("underwater bratva")
	text_1 = myfont.render(str(int(clock.get_fps())),False,(WHITE))
	world = WORLD()
	world_created = False
	while not world_created:
		screen.fill(BACKGROUND)
		new_world = world.world_c()
		for f in range(int(500)):
			world.spawn(new_world, "fish")
		for s in range(int(100)):
			world.spawn(new_world, "shark")
		world_created = True

	running = True
	while running:
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				running = False
			elif event.type == pygame.MOUSEBUTTONDOWN:
				None

		if chronons > 0:
			for creature in Creature.instances:
				creature.check_status(new_world)
			world.update(new_world, screen,chronons)
			chronons -= 1

		pygame.display.flip()
		clock.tick(60)
	pygame.quit()
	sys.exit()
if __name__ == '__main__':
	main()