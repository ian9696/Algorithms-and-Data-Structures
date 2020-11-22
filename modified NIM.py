'''

modified NIM

Competitive Programming 1 (Spring 2018)
Assignment 22 (Week 15) - Nim
https://oj.nctu.edu.tw/problems/493/

written by frank

'''

input()
ans=0
for _ in input().split():
    ans^=len(bin(int(_)))-2
print('win' if ans==0 else 'lose')
