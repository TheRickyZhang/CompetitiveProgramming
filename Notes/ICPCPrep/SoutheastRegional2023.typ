A: 1200
Can greedily keep track of largest imbalance.

B: 1600
Not confident on approach: Can hash each node state as a 3-tuple. For each v, count u-v paths by map count of hash. Update dynamically over DFS

C: 2800?
No idea where to even start with an efficient solution. Maybe you can binary search on how many you can cover?

D: Ordered Problem Set - 1200
Create max sparse table and try every value of k

E: Eccentric Excursion - 3000??
Let x = number of total "forks" when leaf is at node. For instance: 0->[1, 2, 3] has 2 forks.
Then the minimum number of k-edges needed when u is root is x+1 - deg(u). Call this our flight balance.
Pick the lowest node with balance <= k as root.
Go through next unvisited nodes in order value. If, after removing the u->anc(v) edge and adding the u->v edge, the node balance <= k, go to v. Keep doing this.

The only issue is that you might end up using less than k flights. So you might need to go over all options?

You can consider doing a dp of creating disjoint paths, ie each middle vertex has degree 2 from parent edge + some of child edges but this doesn't give a way to get optimal path

F: Matrix Fraud - 2700
Represent cost in 2D DP, where d[i][j] = cumulative min cost so that row i's block ends at j.
Have easy way to query cost(row i, col l, col r)
Then d[i][j] = min over k in [0, j] : d[i-1][suff(k)] + cost(i, pre[k+1])
This seems tricky to compute quickly

G: On-Call Team - 2000
We want to find max k such that for x = 1->k activated bits, the size of matching people, or n - (subsets of ~bitset) >= x.
So we just need to do a sum over subsets of the negated bits covered

H: Range Editing - 2200
Seems like standard range DP, except n = 800, so we need the optimized n^2 log n solution
Compress out consecutive values, then map values to positions to do optimal splits over matching values less than the currrent value: check min with dp[prev] + 1 + dp[middle] (check min with x: ...x...x)

