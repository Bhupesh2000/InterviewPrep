/*
Assignment 8 Q6

You are given two arrays: deadline[], and profit[], which represent a set of jobs, where each job is associated with a deadline, and a profit. Each job takes 1 unit of time to complete, and only one job can be scheduled at a time. You will earn the profit associated with a job only if it is completed by its deadline.

Your task is to find:
The maximum number of jobs that can be completed within their deadlines.
The total maximum profit earned by completing those jobs.

Examples :
Input: deadline[] = [4, 1, 1, 1], profit[] = [20, 10, 40, 30]
Output: [2, 60]
Explanation: Job1 and Job3 can be done with maximum profit of 60 (20+40).

Input: deadline[] = [2, 1, 2, 1, 1], profit[] = [100, 19, 27, 25, 15]
Output: [2, 127]
Explanation: Job1 and Job3 can be done with maximum profit of 127 (100+27).

Input: deadline[] = [3, 1, 2, 2], profit[] = [50, 10, 20, 30]
Output: [3, 100]
Explanation: Job1, Job3 and Job4 can be completed with a maximum profit of 100 (50 + 20 + 30).

Constraints:
1 ≤ deadline.size() == profit.size() ≤ 10^5
1 ≤ deadline[i] ≤ deadline.size()
1 ≤ profit[i] ≤ 500
*/

class Job{
public:
    int id, deadline, profit;
    Job(int id, int deadline, int profit){
        this -> id = id;
        this -> deadline = deadline;
        this -> profit = profit;
    }
};

struct Compare{
    bool operator()(Job& a, Job& b){
        return a.profit > b.profit;
    }
};

class Solution {
  public:
    vector<int> jobSequencing(vector<int> &deadline, vector<int> &profit) {
        // code here
        int n = deadline.size();
        int maxDays = 0;
        vector<Job> jobData;
        for(int i = 0; i < n; i++){
            maxDays = max(maxDays, deadline[i]);
            jobData.push_back(Job(i, deadline[i], profit[i]));
        }
        
        sort(jobData.begin(), jobData.end(), Compare());
        
        vector<int> days(maxDays + 1, -1);
        int totalProfit = 0, count = 0;
        for(int i = 0; i < n; i++){
            int currDeadline = jobData[i].deadline;
            if(days[currDeadline] == -1){
                days[currDeadline] = jobData[i].id;
                totalProfit += jobData[i].profit;
                count ++;
            }
            else{
                for(int j = currDeadline - 1; j > 0; j--){
                    if(days[j] == -1){
                        days[j] = jobData[i].id;
                        totalProfit += jobData[i].profit;
                        count ++;
                        break;
                    }
                }
            }
        }
        
        return vector<int>{count, totalProfit};
    }
};

TC  - O(N) - for filling vector jobData + O(NlogN) -> for sorting + O(N * maxDeadline) -> for core part
SC - O(N) - for jobData + O(maxDeadline)

This will probably work for interviews.
But can be improved using DSU technique(Competitive programming)


class Solution {
  public:
    vector<int> jobSequencing(vector<int> &deadline, vector<int> &profit) {
        vector<pair<int,int>> vp;
        int n = deadline.size(), jobs = 0, maxProfit = 0;
        for(int i = 0; i < n; i++) vp.push_back({deadline[i], profit[i]});
        sort(vp.begin(),vp.end());
        priority_queue<int> pq;
        int index =  n - 1;
        for(int i = vp[n - 1].first; i >= 1; i--){
            while(index >= 0 && i == vp[index].first){
                pq.push(vp[index].second);
                index--;
            }
            if(!pq.empty()){
                jobs++;
                maxProfit += pq.top();
                pq.pop();
            }
        }
        return {jobs,maxProfit};
    }
};

TC - O(NlogN)