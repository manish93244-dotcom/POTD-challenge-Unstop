class SegmentTree {
    constructor(n, initialArray) {
        this.n = n;
        // 4 * N nodes, each storing a frequency array of size 8
        this.tree = Array.from({ length: 4 * n }, () => new Int32Array(8));
        this.lazy = new Uint8Array(4 * n);
        this.build(1, 0, n - 1, initialArray);
    }

    build(node, start, end, arr) {
        if (start === end) {
            this.tree[node][arr[start]] = 1;
            return;
        }
        const mid = (start + end) >> 1;
        const left = node << 1;
        const right = left | 1;
        
        this.build(left, start, mid, arr);
        this.build(right, mid + 1, end, arr);
        
        for (let s = 0; s < 8; s++) {
            this.tree[node][s] = this.tree[left][s] + this.tree[right][s];
        }
    }

    push(node) {
        const mask = this.lazy[node];
        if (mask === 0) return;

        const left = node << 1;
        const right = left | 1;

        // Apply lazy mask to left child
        const tempLeft = new Int32Array(8);
        for (let s = 0; s < 8; s++) tempLeft[s ^ mask] = this.tree[left][s];
        this.tree[left].set(tempLeft);
        this.lazy[left] ^= mask;

        // Apply lazy mask to right child
        const tempRight = new Int32Array(8);
        for (let s = 0; s < 8; s++) tempRight[s ^ mask] = this.tree[right][s];
        this.tree[right].set(tempRight);
        this.lazy[right] ^= mask;

        this.lazy[node] = 0;
    }

    updateRange(node, start, end, l, r, mask) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            const temp = new Int32Array(8);
            for (let s = 0; s < 8; s++) temp[s ^ mask] = this.tree[node][s];
            this.tree[node].set(temp);
            this.lazy[node] ^= mask;
            return;
        }
        this.push(node);
        const mid = (start + end) >> 1;
        this.updateRange(node << 1, start, mid, l, r, mask);
        this.updateRange((node << 1) | 1, mid + 1, end, l, r, mask);
        
        const left = node << 1;
        const right = left | 1;
        for (let s = 0; s < 8; s++) {
            this.tree[node][s] = this.tree[left][s] + this.tree[right][s];
        }
    }

    queryRange(node, start, end, l, r, resultCounts) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            for (let s = 0; s < 8; s++) {
                resultCounts[s] += this.tree[node][s];
            }
            return;
        }
        this.push(node);
        const mid = (start + end) >> 1;
        this.queryRange(node << 1, start, mid, l, r, resultCounts);
        this.queryRange((node << 1) | 1, mid + 1, end, l, r, resultCounts);
    }
}

function processEvents(n, q, receptors, events) {
    const segTree = new SegmentTree(n, receptors);
    const results = [];

    for (let i = 0; i < q; i++) {
        const event = events[i];
        const type = event[0];
        const l = event[1] - 1; // Convert 1-based index to 0-based
        const r = event[2] - 1;

        if (type === 1) {
            const m = event[3];
            segTree.updateRange(1, 0, n - 1, l, r, m);
        } else if (type === 2) {
            const resultCounts = new Int32Array(8);
            segTree.queryRange(1, 0, n - 1, l, r, resultCounts);
            
            // Find the maximum frequency among all 8 states
            let maxFreq = 0;
            for (let s = 0; s < 8; s++) {
                if (resultCounts[s] > maxFreq) {
                    maxFreq = resultCounts[s];
                }
            }
            results.push(maxFreq);
        }
    }

    return results;
}

function main() {
    const fs = require('fs');
    const input = fs.readFileSync('/dev/stdin', 'utf8');
    const data = input.trim().split(/\s+/);
    if (data.length === 0 || data[0] === "") return;

    let idx = 0;
    const n = parseInt(data[idx++], 10);
    const q = parseInt(data[idx++], 10);
    const receptors = [];
    for (let i = 0; i < n; i++) {
        receptors.push(parseInt(data[idx++], 10));
    }
    
    const events = [];
    for (let i = 0; i < q; i++) {
        const type = parseInt(data[idx++], 10);
        const l = parseInt(data[idx++], 10);
        const r = parseInt(data[idx++], 10);
        
        if (type === 1) {
            const m = parseInt(data[idx++], 10);
            events.push([type, l, r, m]);
        } else {
            events.push([type, l, r]);
        }
    }
    
    const results = processEvents(n, q, receptors, events);
    results.forEach(result => console.log(result));
}

main();