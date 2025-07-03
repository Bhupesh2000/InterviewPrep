/*
Assignment 6 Q6
https://www.hackerrank.com/challenges/maximum-element/problem

You are given an empty stack. You will receive N queries. Each query is one of the following:
1 x → Push the number x onto the stack.
2 → Pop (remove) the number on the top of the stack.
3 → Print the maximum number currently in the stack.
Your task is to return a list of results from all the type-3 queries (i.e., every time someone asks for the current maximum).

Input
10
1 97
2
1 20
2
1 26
1 20
2
3
1 91
3
Explanation:
Push 97 → Stack: [97]
Pop → Stack becomes empty
Push 20 → Stack: [20]
Pop → Stack becomes empty
Push 26 → Stack: [26]
Push 20 → Stack: [26, 20]
Pop → Stack: [26]
Type 3 → Max is 26 → Output: 26
Push 91 → Stack: [26, 91]
Type 3 → Max is 91 → Output: 91
Output - 
26
91

operations[] size n = 10
operations = ['1 97', '2', '1 20', ....]

*/

Using ordered_map
/*
 * Complete the 'getMax' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts STRING_ARRAY operations as parameter.
 */

vector<int> getMax(vector<string> operations) {
    vector<int> ans;
    map<int, int> mp;
    stack<int> st;
    
    for(int i = 0; i < static_cast<int>(operations.size()); i++){
        if(operations[i] == "2"){
            if(st.empty()) continue;
            int topElement = st.top();
            st.pop();
            mp[topElement] --;
            if (mp[topElement] == 0) {
                mp.erase(topElement);
            }
        }
        else if(operations[i] == "3"){
            if(st.empty()) continue;
            auto it = mp.rbegin();
            ans.push_back(it -> first);
        }
        else{
            string s = operations[i].substr(2);
            int a = stoi(s);
            mp[a] ++;
            st.push(a);
        }
    }
    
    return ans;
}

🔍 Time Complexity (TC):

Type 1: 1 x (push)
st.push(x) → O(1)

mp[x]++ → O(log n) (because insertion/update in an ordered map is log n)

Type 2: 2 (pop)
st.pop() → O(1)

mp[topElement]-- → O(log n)

Erase check: if (mp[topElement] == 0) mp.erase(topElement) → O(log n)

Type 3: 3 (get max)
mp.rbegin() → O(1) access (just a pointer to the last element)

So:

🔸 Each operation is at most O(log n)
✅ Total Time Complexity: O(q × log n)
Where q is the number of operations, and n is the number of unique elements in the stack at a time.

💾 Space Complexity (SC):
stack<int> st → stores up to q elements → O(q)

map<int, int> mp → stores frequency of each unique element → at most q unique keys → O(q)

✅ Total Space Complexity: O(q)

📌 Final Answer:
Time Complexity: O(q × log n)

Space Complexity: O(q)

--------------------------------------------------------------------------------------------------------------------------------------------

Using 2 stacks

vector<int> getMax(vector<string> operations) {
    vector<int> ans;
    stack<int> elements; // store all elements
    stack<int> maxElement; // stores only the maxElements till the pt.
    
    for(int i = 0; i < static_cast<int>(operations.size()); i++){
        // pop element
        if(operations[i] == "2"){
            if(elements.empty()) continue;
            // pop from maxElements if the topElement is the max till the pt.
            if(maxElement.top() == elements.top()){
                maxElement.pop();
            }
            // pop from elements
            elements.pop();
        }
        // return max element
        else if(operations[i] == "3"){
            if(maxElement.empty()) continue;
            ans.push_back(maxElement.top());
        }
        // push element
        else{
            // get the integer element
            string s = operations[i].substr(2);
            int a = stoi(s);
            // push into element
            elements.push(a);
            // push into maxElements if max till pt.
            if(maxElement.empty() || maxElement.top() <= a) maxElement.push(a);
        }
    }
    return ans;
}

TC - q * O(1) -> q is the number of queries.
SC - O(q) -> for the extra stack(maxElements), which will store max q elements in worst case when all queries are push