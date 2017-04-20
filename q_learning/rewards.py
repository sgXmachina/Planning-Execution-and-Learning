import matplotlib.pyplot as plt

f = open('test2.txt');

rewards =[]
it = []

i = 0

for line in f.readlines():
	rewards.append(int(line))
	i+=1
	it.append(i)

plt.scatter(it, rewards)
plt.show()