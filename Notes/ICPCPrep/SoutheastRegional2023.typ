A: ABC String - 1200 (Actual: +200)
Can greedily keep track of largest imbalance.

B: Balanced Tree Path - 1600 (Actual: +200)
Not confident on approach: Can hash each node state as a 3-tuple. For each v, count u-v paths by map count of hash. Update dynamically over DFS

C: Cramming for Finals - 2800? (Actual: -300 but still very hard)
No idea where to even start with an efficient solution. Maybe you can binary search on how many you can cover?

D: Ordered Problem Set - 1200
Create max sparse table and try every value of k

E: Eccentric Excursion - 3000?? (Actual: 0 solves)
Let x = number of total "forks" when leaf is at node. For instance: 0->[1, 2, 3] has 2 forks.
Then the minimum number of k-edges needed when u is root is x+1 - deg(u). Call this our flight balance.
Pick the lowest node with balance <= k as root.
Go through next unvisited nodes in order value. If, after removing the u->anc(v) edge and adding the u->v edge, the node balance <= k, go to v. Keep doing this.

The only issue is that you might end up using less than k flights. So you might need to go over all options?

You can consider doing a dp of creating disjoint paths, ie each middle vertex has degree 2 from parent edge + some of child edges but this doesn't give a way to get optimal path

F: Matrix Fraud - 2700 (Actual: -400)
Represent cost in 2D DP, where d[i][j] = cumulative min cost so that row i's block ends at j.
Have easy way to query cost(row i, col l, col r)
Then d[i][j] = min over k in [0, j] : d[i-1][suff(k)] + cost(i, pre[k+1])
This seems tricky to compute quickly

G: On-Call Team - 2000
We want to find max k such that for x = 1->k activated bits, the size of matching people, or n - (subsets of ~bitset) >= x.
So we just need to do a sum over subsets of the negated bits covered

H: Range Editing - 2200 (Actual: -200)
Seems like standard range DP, except n = 800, so we need the optimized solution. Still O(n^3), but very often n^2.
Compress out consecutive values, then map values to positions to do optimal splits over matching values less than the currrent value: check min with dp[prev] + 1 + dp[middle] (check min with x: ...x...x)

I: Item Selection - 1500
You can just do a greedy algorithm. On each page, take the min(deselect bad, select good, unselect all, select good, select all, deselect bad).

J: Sequence Guessing - 1200 (Actual: +600)
Just set the sequence as 0, a0, 3, a1, 6, ... 99999, 100000.

K: Streets Behind - 1700
Pretty simple greedy algorithm for simulating, but if a/b is very small then it probably TLEs.
Can binary search until the $x = min(k, floor(n * a/b))$ term changes, to do bulk updates of n, k.

L: Segment Drawing - 2800 (Actual: 0 solves)
I don't know. Probably some strategy with processing by segment end time, and some type of convex hull greedy choosing?

M: Champernowne Verification - 900
Easy string check


