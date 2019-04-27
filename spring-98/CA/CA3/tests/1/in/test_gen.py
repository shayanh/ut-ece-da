from random import randint, choice, sample

prefix = "./in/"
for i in range(40):
	testName = ""
	if(i < 10):
		testName = "input0{}.txt".format(i)
	else:
		testName = "input{}.txt".format(i)

	with open("{}{}".format(prefix, testName), "w+") as f:
		n = randint(2, 3 + 10**(i/10))
		m = randint(0, (n*n-1)/2 - 1)
		f.write("{} {}\n".format(n, m))
		l = []
		for x in range(1, n+1):
			for y in range(x+1, n+1):
				t = randint(1, 1 + 10**(i/10 if i/10 == 0 else i/10 - 1))
				l.append((x, y, t))			
		samples = sample(l, m)
		for a, b, t in samples:
			f.write("{} {} {}\n".format(a, b, t))
		for _ in range(n):
			ki = randint(0, 1 + (i/10))
			l = [x for x in range(10**(i/10))]
			ki_ts = sample(l, ki)
			f.write("{} {}\n".format(ki, " ".join(map(str, ki_ts))))
