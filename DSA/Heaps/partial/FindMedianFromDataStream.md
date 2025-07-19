/*
Assignment 8 Q16
https://leetcode.com/problems/find-median-from-data-stream

The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.
For example, for arr = [2,3,4], the median is 3.
For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
Implement the MedianFinder class:
MedianFinder() initializes the MedianFinder object.
void addNum(int num) adds the integer num from the data stream to the data structure.
double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.
 
Example 1:
Input
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output
[null, null, null, 1.5, null, 2.0]
Explanation
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
 
Constraints:
-10^5 <= num <= 10^5
There will be at least one element in the data structure before calling findMedian.
At most 5 * 10^4 calls will be made to addNum and findMedian.

Follow up:
If all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
If 99% of all integer numbers from the stream are in the range [0, 100], how would you optimize your solution?
*/

Approach 1 - using vector and inplace sorting

class MedianFinder {
    vector<int> v;
public:
    MedianFinder() {
    }
    
    void addNum(int num) {
        v.push_back(num);
        int pivot = v.size() - 1;
        for(int i = v.size() - 2; i >= 0; i--){
            if(v[i] > v[pivot]){
                swap(v[i], v[pivot]);
                pivot = i;
            }
            else break;
        }
    }
    
    double findMedian() {
        if(v.size() % 2 != 0) return (double) v[v.size() / 2];
        else return ((double)v[v.size() / 2] + (double)v[v.size() / 2 - 1]) / 2;
    }
};

TC - O(N*N), SC - O(N)

--------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 - using two heaps(max and min)

class MedianFinder {
    priority_queue<int> left;
    priority_queue<int, vector<int>, greater<int>> right;
public:
    MedianFinder() {
    }
    
    void addNum(int num) {
        if(left.size() == 0){
            left.push(num);
            return;
        }

        if(num > left.top()) right.push(num);
        else left.push(num);

        if(left.size() - right.size() == 2){
            right.push(left.top());
            left.pop();
        }
        else if(right.size() - left.size() == 2){
            left.push(right.top());
            right.pop();
        }
    }
    
    double findMedian() {
        if(left.size() == right.size()) return (double)((double)left.top() + (double)right.top()) / 2;
        else if(left.size() > right.size()) return left.top();
        else return right.top();
    }
};

TC - O(n * logn), SC - O(2N)


Follow up questions - 
✅ Follow-up 1: All numbers are in the range [0, 100]
🔧 Optimization Strategy: Counting Sort with Prefix Sum
If all numbers are guaranteed to be in [0, 100], you don’t need to store the actual list or use heaps. Instead:

Use an array of size 101: int count[101] = {0};

Maintain int total = 0; to track the total number of elements.

In addNum(num), just do:
count[num]++; total++;

In findMedian(), iterate through count array to find the middle(s).

🧠 Why this works:
The range is fixed and small → constant space.

Finding the median from the frequency array is O(100) = O(1) time.

✅ Follow-up 2: 99% of numbers are in [0, 100], but some may be outside
🔧 Optimization Strategy: Hybrid Approach (Counting + Heaps)
Use the same count[101] array for numbers in [0, 100].

Use two heaps:

One for numbers < 0

One for numbers > 100

Track counts separately:

countInRange → numbers in [0, 100]

countLow → numbers < 0

countHigh → numbers > 100

In findMedian():
Use the total count to find where the median lies:

If it's in [0, 100], scan count[] as before.

If not, peek into the appropriate heap(s) to find it.