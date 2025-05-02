#include <bits/stdc++.h>
using namespace std;

static const int B = 60;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read Alice's fixed heaps
    int n;
    cin >> n;
    vector<unsigned long long> alice(n);
    for(int i = 0; i < n; i++)
        cin >> alice[i];

    // Read Bob's boxes and build the ground set
    int m;
    cin >> m;
    vector<vector<int>> box_elems(m);
    vector<int> elem_box;
    vector<unsigned long long> vals;
    for(int b = 0; b < m; b++){
        int k;
        cin >> k;
        box_elems[b].reserve(k);
        while(k--){
            unsigned long long x;
            cin >> x;
            int idx = vals.size();
            vals.push_back(x);
            elem_box.push_back(b);
            box_elems[b].push_back(idx);
        }
    }

    int E = vals.size();
    vector<bool> inS(E, false);
    vector<int> pick(m, -1);

    // Basis for linear matroid
    array<unsigned long long, B> basis = {};
    array<int, B> basis_id = {};

    auto insert_basis = [&](unsigned long long x, int id){
        for(int b = B - 1; b >= 0; b--){
            if(!(x >> b & 1)) continue;
            if(!basis[b]){
                basis[b] = x;
                basis_id[b] = id;
                return;
            }
            x ^= basis[b];
        }
    };

    auto reduce_with_circuit = [&](unsigned long long x, vector<int>& circuit){
        circuit.clear();
        for(int b = B - 1; b >= 0; b--){
            if(!(x >> b & 1)) continue;
            if(!basis[b])
                return x;
            circuit.push_back(basis_id[b]);
            x ^= basis[b];
        }
        return 0ULL;
    };

    vector<int> parent(E), vis(E);
    queue<int> q;

    // Try to augment the common independent set by 1
    auto augment = [&](){
        // Rebuild basis from Alice + current picks
        fill(basis.begin(), basis.end(), 0);
        for(auto x : alice)
            insert_basis(x, -1);
        for(int i = 0; i < E; i++)
            if(inS[i])
                insert_basis(vals[i], i);

        // Prepare BFS
        fill(vis.begin(), vis.end(), 0);
        fill(parent.begin(), parent.end(), -1);
        while(!q.empty()) q.pop();

        // Enqueue all elements from boxes not yet represented
        for(int i = 0; i < E; i++){
            int b = elem_box[i];
            if(!inS[i] && pick[b] == -1){
                vis[i] = 1;
                q.push(i);
            }
        }

        int sink = -1;
        vector<int> circuit;

        // BFS on exchange graph
        while(!q.empty() && sink < 0){
            int u = q.front(); q.pop();
            if(!inS[u]){
                // Try to add u to the linear basis
                unsigned long long rem = reduce_with_circuit(vals[u], circuit);
                if(rem){
                    sink = u;
                    break;
                }
                // Otherwise follow circuit edges u -> each v in circuit
                for(int v : circuit){
                    if(!vis[v]){
                        vis[v] = 1;
                        parent[v] = u;
                        q.push(v);
                    }
                }
            } else {
                // u is in S: can swap within its box
                int b = elem_box[u];
                for(int v : box_elems[b]){
                    if(!inS[v] && !vis[v]){
                        vis[v] = 1;
                        parent[v] = u;
                        q.push(v);
                    }
                }
            }
        }

        if(sink < 0)
            return false;

        // Flip along the augmenting path
        bool add = true;
        for(int cur = sink; cur >= 0; cur = parent[cur], add = !add){
            int b = elem_box[cur];
            if(add){
                inS[cur] = true;
                pick[b] = cur;
            } else {
                inS[cur] = false;
                pick[b] = -1;
            }
        }
        return true;
    };

    // Perform up to m augmentations
    while(augment());

    // Check result
    for(int b = 0; b < m; b++){
        if(pick[b] < 0){
            cout << -1 << "\n";
            return 0;
        }
    }
    // Output the chosen heap sizes
    for(int b = 0; b < m; b++){
        cout << vals[pick[b]] << (b + 1 < m ? ' ' : '\n');
    }
    return 0;
}
