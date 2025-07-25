/*
Assignment 8 Q5
https://www.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1

You are given timings of n meetings in the form of (start[i], end[i]) where start[i] is the start time of meeting i and end[i] is the finish time of meeting i. Return the maximum number of meetings that can be accommodated in a single meeting room, when only one meeting can be held in the meeting room at a particular time. 
Note: The start time of one chosen meeting can't be equal to the end time of the other chosen meeting.

Examples :
Input: start[] = [1, 3, 0, 5, 8, 5], end[] =  [2, 4, 6, 7, 9, 9]
Output: 4
Explanation: Maximum four meetings can be held with given start and end timings. The meetings are - (1, 2), (3, 4), (5,7) and (8,9)

Input: start[] = [10, 12, 20], end[] = [20, 25, 30]
Output: 1
Explanation: Only one meetings can be held with given start and end timings.

Input: start[] = [1, 2], end[] = [100, 99]
Output: 1
Constraints:
1 ≤ n ≤ 10^5
0 ≤ start[i] < end[i] ≤ 10^6
*/

class Meet{
public:
    int id;
    int startTime;
    int endTime;
    Meet(int id, int start, int end){
        this -> id = id;
        this -> startTime = start;
        this -> endTime = end;
    }
};

struct Compare{
    bool operator()(const Meet& a, const Meet& b){
        return a.endTime < b.endTime;
    }
};

class Solution {
  public:
    // Function to find the maximum number of meetings that can
    // be performed in a meeting room.
    int maxMeetings(vector<int>& start, vector<int>& end) {
        // Your code here
        int n = start.size();
        vector<Meet> meetings;
        for(int i = 0; i < n; i++){
            meetings.push_back(Meet(i, start[i], end[i]));
        }
        sort(meetings.begin(), meetings.end(), Compare());
        
        int count = 0;
        int currMeetEndTime = -1;
        for(int i = 0; i < n; i++){
            if(meetings[i].startTime > currMeetEndTime){
                count ++;
                currMeetEndTime = meetings[i].endTime;
            }
        }
        
        return count;
    }
};

TC - O(NlogN), SC - O(N)