class SegmentTree {
    constructor(size) {
        this.size = size;
        this.tree = new Int32Array(4 * size);
        this.lazy = new Uint8Array(4 * size);
    }

    push(node, start, end) {
        if (this.lazy[node] === 0) return;
        
        let mid = (start + end) >> 1;
        let left = node << 1;
        let right = left | 1;

        // Toggle left child
        this.tree[left] = (mid - start + 1) - this.tree[left];
        this.lazy[left] ^= 1;

        // Toggle right child
        this.tree[right] = (end - mid) - this.tree[right];
        this.lazy[right] ^= 1;

        this.lazy[node] = 0;
    }

    updateRange(node, start, end, l, r) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            this.tree[node] = (end - start + 1) - this.tree[node];
            this.lazy[node] ^= 1;
            return;
        }
        this.push(node, start, end);
        let mid = (start + end) >> 1;
        this.updateRange(node << 1, start, mid, l, r);
        this.updateRange((node << 1) | 1, mid + 1, end, l, r);
        this.tree[node] = this.tree[node << 1] + this.tree[(node << 1) | 1];
    }

    queryRange(node, start, end, l, r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return this.tree[node];
        this.push(node, start, end);
        let mid = (start + end) >> 1;
        return this.queryRange(node << 1, start, mid, l, r) +
               this.queryRange((node << 1) | 1, mid + 1, end, l, r);
    }
}

function processQueries(n, edges, queries) {
    const adj = Array.from({ length: n + 1 }, () => []);
    for (const [u, v] of edges) {
        adj[u].push(v);
        adj[v].push(u);
    }

    const parent = new Int32Array(n + 1);
    const depth = new Int32Array(n + 1);
    const heavy = new Int32Array(n + 1).fill(-1);
    const head = new Int32Array(n + 1);
    const pos = new Int32Array(n + 1);
    let curPos = 0;

    // Iterative DFS to compute size, parent, depth, and heavy child without stack overflow
    const stack = [1];
    const visited = new Uint8Array(n + 1);
    const size = new Int32Array(n + 1);
    const edgeIdx = new Int32Array(n + 1);
    
    while (stack.length > 0) {
        const u = stack[stack.length - 1];
        if (!visited[u]) {
            visited[u] = 1;
            edgeIdx[u] = 0;
        }

        if (edgeIdx[u] < adj[u].length) {
            const v = adj[u][edgeIdx[u]++];
            if (v !== parent[u]) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                stack.push(v);
            }
        } else {
            stack.pop();
            size[u] = 1;
            let maxSubtree = 0;
            for (const v of adj[u]) {
                if (v !== parent[u]) {
                    size[u] += size[v];
                    if (size[v] > maxSubtree) {
                        maxSubtree = size[v];
                        heavy[u] = v;
                    }
                }
            }
        }
    }

    // Decompose into chains
    const hldStack = [1];
    head[1] = 1;
    while (hldStack.length > 0) {
        const u = hldStack.pop();
        pos[u] = curPos++;
        
        // Process light children first so that heavy child stays at top of stack
        for (const v of adj[u]) {
            if (v !== parent[u] && v !== heavy[u]) {
                head[v] = v;
                hldStack.push(v);
            }
        }
        if (heavy[u] !== -1) {
            head[heavy[u]] = head[u];
            hldStack.push(heavy[u]);
        }
    }

    const segTree = new SegmentTree(n);

    function modifyPath(u, v) {
        while (head[u] !== head[v]) {
            if (depth[head[u]] > depth[head[v]]) {
                segTree.updateRange(1, 0, n - 1, pos[head[u]], pos[u]);
                u = parent[head[u]];
            } else {
                segTree.updateRange(1, 0, n - 1, pos[head[v]], pos[v]);
                v = parent[head[v]];
            }
        }
        if (u !== v) {
            if (depth[u] > depth[v]) {
                segTree.updateRange(1, 0, n - 1, pos[v] + 1, pos[u]);
            } else {
                segTree.updateRange(1, 0, n - 1, pos[u] + 1, pos[v]);
            }
        }
    }

    function queryPath(u, v) {
        let res = 0;
        while (head[u] !== head[v]) {
            if (depth[head[u]] > depth[head[v]]) {
                res += segTree.queryRange(1, 0, n - 1, pos[head[u]], pos[u]);
                u = parent[head[u]];
            } else {
                res += segTree.queryRange(1, 0, n - 1, pos[head[v]], pos[v]);
                v = parent[head[v]];
            }
        }
        if (u !== v) {
            if (depth[u] > depth[v]) {
                res += segTree.queryRange(1, 0, n - 1, pos[v] + 1, pos[u]);
            } else {
                res += segTree.queryRange(1, 0, n - 1, pos[u] + 1, pos[v]);
            }
        }
        return res;
    }

    // Process type 1 and type 2 queries sequentially
    for (const [type, u, v] of queries) {
        if (type === 1) {
            modifyPath(u, v);
        } else if (type === 2) {
            console.log(queryPath(u, v));
        }
    }
}

function main() {
    const input = require('fs').readFileSync('/dev/stdin', 'utf8');
    const data = input.trim().split(/\s+/);
    if (data.length === 0 || data[0] === '') return;
    
    let index = 0;
    const n = parseInt(data[index++], 10);
    const edges = [];
    for (let i = 0; i < n - 1; i++) {
        const a = parseInt(data[index++], 10);
        const b = parseInt(data[index++], 10);
        edges.push([a, b]);
    }
    const q = parseInt(data[index++], 10);
    const queries = [];
    for (let i = 0; i < q; i++) {
        const t = parseInt(data[index++], 10);
        const u = parseInt(data[index++], 10);
        const v = parseInt(data[index++], 10);
        queries.push([t, u, v]);
    }

    processQueries(n, edges, queries);
}

main();
