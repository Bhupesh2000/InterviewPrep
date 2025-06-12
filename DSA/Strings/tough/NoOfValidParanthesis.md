/*
Given a number n, the task is to find the number of valid parentheses expressions of that length. 
Examples : 

Input: 2
Output: 1 
Explanation: There is only possible valid expression of length 2, "()"

Input: 4
Output: 2 
Explanation: Possible valid expression of length 4 are "(())" and "()()" 

Input: 6
Output: 5
Explanation: Possible valid expressions are ((())), ()(()), ()()(), (())() and (()())
*/

TC - O(2^n)

int findNoOfParanthesis(int left, int right, int &ans) {
    // Invalid state: too many '(' with no ')' to balance
    if (left > right) return 0;

    // Valid complete sequence
    if (left == 0 && right == 0) {
        ans++;
        return ans;
    }

    // Place a '(' if available
    if (left > 0) {
        findNoOfParanthesis(left - 1, right, ans);
    }

    // Place a ')' if available
    if (right > 0) {
        findNoOfParanthesis(left, right - 1, ans);
    }

    return ans;
}

int findNoOfParanthesis(int n) {
    if (n % 2 != 0) return 0; // odd length can't be valid
    int ans = 0;
    return findNoOfParanthesis(n / 2, n / 2, ans);
}

--------------------------------------------------------------------------------------------------------------------------------------------

TC - O(n^2)

/*
 * Recursive function to count the number of valid parentheses combinations
 * for a given number of `pairs` of parentheses.
 * 
 * This uses the Catalan number recurrence:
 *   C(n) = Σ (C(i) * C(n - 1 - i)) for i = 0 to n - 1
 * 
 * Each valid expression can be split as:
 *   '(' + valid_expression(i) + ')' + valid_expression(n - 1 - i)
 */
int countValidParens(int pairs) {
    // Base case: only one valid expression of 0 pairs — the empty string
    if (pairs == 0) return 1;

    int ans = 0;

    // Loop over all ways to divide the pairs into "inside" and "outside"
    // of the first outermost '(' and ')'
    for (int i = 0; i < pairs; i++) {
        // LEFT: valid expressions that go inside the first pair of parentheses
        int left = countValidParens(i);

        // RIGHT: valid expressions that go after the first pair of parentheses
        // We subtract 1 because one pair is used by the outermost '()'
        int right = countValidParens(pairs - 1 - i);

        // Total ways for this split is the product of combinations
        ans += left * right;
    }

    return ans;
}

/*
 * Main function to calculate number of valid parentheses sequences
 * given a total number of characters `n`.
 * Only even values of `n` are valid (since '(' and ')' come in pairs).
 */
int findNoOfParanthesis(int n) {
    // Odd length strings can never form valid pairs
    if (n % 2 != 0) return 0;

    int pairs = n / 2; // Number of '(' or ')' pairs
    return countValidParens(pairs);
}

--------------------------------------------------------------------------------------------------------------------------------------------

TC - O(n)
Using Catalan Number
// For n pairs of parentheses, the number of valid combinations is the n-th Catalan number:
// Catalan number C(n) = (2n)! / ((n + 1)! * n!)
// Equivalent to: C(n) = binomialCoeff(2n, n) / (n + 1)

// Function to compute binomial coefficient C(2n, n)
long long binomialCoeff(int n) {
    long long res = 1;

    // Compute (2n)! / (n! * n!) iteratively to avoid overflow
    for (int i = 0; i < n; ++i) {
        res *= (2 * n - i);
        res /= (i + 1);
    }

    return res;
}

// Function to compute Catalan number in O(n)
long long catalan(int n) {
    long long c = binomialCoeff(n);
    return c / (n + 1);
}

// Wrapper function to calculate valid parentheses arrangements
int findNoOfParanthesis(int totalChars) {
    // Odd-length strings can't be valid
    if (totalChars % 2 != 0) return 0;

    int pairs = totalChars / 2;
    return catalan(pairs);
}

