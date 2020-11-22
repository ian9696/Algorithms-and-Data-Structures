'''

min b s.t. lcm(a, b)=c, LCM, GCD, howard

Competitive Programming 1 (Spring 2018)
Assignment 10 (Week 8) - LCM
https://oj.nctu.edu.tw/problems/481/

written by howard

'''

def gcd(a, b):
	return a if b == 0 else gcd(b, a%b)

def lcm(a, b):
	return a*b/gcd(a, b)

q = int(raw_input())

for i in range(q):

	a, c = map(int, raw_input().split(" "))

	if c%a != 0:
		print "-1"
	else:
		b = 1
		while lcm(a, b) != c:
			b = b*c/lcm(a, b)
				
		print b
