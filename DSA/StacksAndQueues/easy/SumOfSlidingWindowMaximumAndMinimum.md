/*
Assignment 6 Q13
https://www.geeksforgeeks.org/sum-minimum-maximum-elements-subarrays-size-k/

Given an array of both positive and negative integers, the task is to compute sum of minimum and maximum elements of all sub-array of size k.

Examples: 
Input : arr[] = {2, 5, -1, 7, -3, -1, -2}  K = 4
Output : 18
Explanation : Subarrays of size 4 are : 
     {2, 5, -1, 7},   min + max = -1 + 7 = 6
     {5, -1, 7, -3},  min + max = -3 + 7 = 4      
     {-1, 7, -3, -1}, min + max = -3 + 7 = 4
     {7, -3, -1, -2}, min + max = -3 + 7 = 4 

Same as Sliding window maximum. Instead of 1 have 2 deques.