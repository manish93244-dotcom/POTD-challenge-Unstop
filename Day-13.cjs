function min_operations(n, E, T) {
    if (n === 0) return 0;

    // Compute the difference array D[i] = T[i] - E[i]
    const D = new Float64Array(n);
    for (let i = 0; i < n; i++) {
        D[i] = T[i] - E[i];
    }

    // Initialize operations with the absolute value of the first sector
    let totalOperations = Math.abs(D[0]);

    for (let i = 1; i < n; i++) {
        const prev = D[i - 1];
        const curr = D[i];

        // Check if the signs are strictly opposite
        if ((prev > 0 && curr < 0) || (prev < 0 && curr > 0)) {
            // Signs are opposite: cannot share any operations
            totalOperations += Math.abs(curr);
        } else {
            // Signs are the same (or one is zero): operations can be shared
            const prevAbs = Math.abs(prev);
            const currAbs = Math.abs(curr);
            if (currAbs > prevAbs) {
                totalOperations += (currAbs - prevAbs);
            }
        }
    }

    return totalOperations;
}

function main() {
    const fs = require('fs');
    const input = fs.readFileSync(0, 'utf8').trim().split('\n');
    if (input.length < 3 || input[0] === '') return;

    const n = parseInt(input[0].trim(), 10);
    const E = input[1].trim().split(/\s+/).map(Number);
    const T = input[2].trim().split(/\s+/).map(Number);

    const result = min_operations(n, E, T);
    console.log(result);
}

main();