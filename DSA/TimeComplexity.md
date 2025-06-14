Input Size N	    |  Expected Time Complexity  |	  Typical Approaches / Algorithms
------------------|----------------------------|----------------------------------------------------------------------------
≤ 10	            |  O(N!), O(2ⁿ)	             |    Brute-force recursion, backtracking, permutations
≤ 20	            |  O(2ⁿ × N), O(N × 2ⁿ)	     |    Bitmasking DP, subset generation, meet-in-the-middle
≤ 100	            |  O(N³)	                   |    Dynamic Programming with triple nested loops, Floyd-Warshall
≤ 1,000	          |  O(N²)	                   |    DP with double loops, adjacency matrix-based graph algorithms
≤ 10⁵ (100,000)	  |  O(N log N), O(N)	         |    Sorting, binary search, prefix sums, hash maps, greedy, segment trees
≤ 10⁶ (1,000,000)	|  O(N)	                     |    Counting, sliding window, hash maps, union-find, sieve
~10⁷ or more	    |  O(N) (with fast I/O)	     |    Array manipulation, prefix sums (optimize I/O with scanf, cin.tie(0))
Up to 10⁹	        |  O(log N)	                 |    Binary search, exponentiation by squaring, number theory
                  |                            |
