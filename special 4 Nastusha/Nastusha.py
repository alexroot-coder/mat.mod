import random
import os
space = []
temp_space = []
X = 50
Y = 50
iterations = 1000
def init():
	for i in range(0, X):
		space.append([])
		temp_space.append([])
		for j in range(0, Y):
			space[i].append(' ')
			temp_space[i].append('')

def init2():
	for i in range(0,X):
		for j in range(0,Y):
			if ((random.randint(0,2367272) % 2) == 0):
				space[i][j] = ' '
			else:
				space[i][j] = chr(9829)

def find_points(space,i,j):
	sosed = 0
	if (space[i+1][j+1] == chr(9829)):
		sosed+=1
	if (space[i][j+1] == chr(9829)):
		sosed+=1
	if (space[i-1][j+1] == chr(9829)):
		sosed+=1
	if (space[i-1][j] == chr(9829)):
		sosed+=1
	if (space[i-1][j-1] == chr(9829)):
		sosed+=1
	if (space[i][j-1] == chr(9829)):
		sosed+=1
	if (space[i+1][j-1] == chr(9829)):
		sosed+=1
	if (space[i+1][j] == chr(9829)):
		sosed+=1
	return sosed

def collisions(space):
	for i in range(0, X - 1):
		for j in range(0, Y - 1):
			sosed1 = find_points(space,i,j)
			if sosed1 < 2:
				temp_space[i][j] = ' '
			elif sosed1 > 3:
				temp_space[i][j] = ' '
			elif (sosed1 == 2 and space[i][j] == chr(9829)):
				temp_space[i][j] = chr(9829)
			elif sosed1 == 3:
				temp_space[i][j] = chr(9829)
	return temp_space

def main():
	init()
	init2()
	for q in range(0, iterations):
		collisions(space)
		for i in range(0, X):
			for j in range(0 ,Y):
				print(space[i][j], end=' ')
			print(' ')

		for i in range(0, X):
			for j in range(0, Y):
				space[i][j] = temp_space[i][j]
		print()
		print('Iterations: ' + str(q))
		input()
		os.system('cls')
	input()

if __name__ == '__main__':
	main()