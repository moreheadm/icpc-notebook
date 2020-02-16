/**
 * Author: Nalin Bhardwaj
 * Date: 2020-02-15
 * License: CC0
 * Source: CP3
 * Description: Computes dfs\_low = minimum dfs number in subtree and dfs\_num. Note AP special case for dfs root.
 * Time: O(N+E)
 */
void dfs(int u) {
	dfs_low[u] = dfs_num[u] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
	for(int j = 0; j < (int)AdjList[u].size(); j++) {
		ii v = AdjList[u][j];
		if(dfs_num[v.first] == UNVISITED) { // a tree edge
			dfs_parent[v.first] = u;
			if (u == dfsRoot) rootChildren++; // special case if u is a root

			dfs(v.first);
			
			if (dfs_low[v.first] >= dfs_num[u]) {
				articulation_vertex[u] = true;
			}
			if (dfs_low[v.first] > dfs_num[u]) {
				printf(" Edge (%d, %d) is a bridge\n", u, v.first);
			}
			dfs_low[u] = min(dfs_low[u], dfs_low[v.first]); // update dfs_low[u]
		}
		else if(v.first != dfs_parent[u]) // a back edge and not direct cycle
			dfs_low[u] = min(dfs_low[u], dfs_num[v.first]); // update dfs_low[u]
	}
}

// inside int main()
dfsNumberCounter = 0;
dfs_num.assign(V, UNVISITED);
dfs_low.assign(V, 0);
dfs_parent.assign(V, 0);
articulation_vertex.assign(V, 0);
for(int i = 0; i < V; i++) {
	if (dfs_num[i] == UNVISITED) {
		dfsRoot = i;
		rootChildren = 0;
		dfs(i);
		articulation_vertex[dfsRoot] = (rootChildren > 1);  // special case
	}
}
