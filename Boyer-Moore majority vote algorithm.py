'''

Boyer-Moore majority vote algorithm

Find majority in an array of numbers

O(n) time, O(1) space

https://leetcode.com/problems/majority-element/

'''

class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        v=0
        c=0
        for x in nums:
            if c==0:
                v=x
                c+=1
            elif x==v:
                c+=1
            else:
                c-=1
        return v
