function maxMutatedViruses(N, contamination_levels) {
    // Find the maximum contamination level to bound our frequency array
    let maxLevel = 0;
    for (let i = 0; i < N; i++) {
        if (contamination_levels[i] > maxLevel) {
            maxLevel = contamination_levels[i];
        }
    }

    // Create a frequency array for the contamination levels
    const count = new Array(maxLevel + 3).fill(0);
    for (let i = 0; i < N; i++) {
        count[contamination_levels[i]]++;
    }

    // dp[j][k] represents the maximum groups formed where:
    // j = number of active sequences that started at i-2 (needing elements at i-1 and i)
    // k = number of active sequences that started at i-1 (needing elements at i and i+1)
    let dp = Array.from({ length: 3 }, () => new Array(3).fill(-1));
    dp[0][0] = 0;

    // Iterate through each contamination level
    for (let i = 1; i <= maxLevel + 2; i++) {
        let nextDp = Array.from({ length: 3 }, () => new Array(3).fill(-1));

        for (let j = 0; j < 3; j++) {
            for (let k = 0; k < 3; k++) {
                if (dp[j][k] === -1) continue;

                // c is the number of new consecutive sequences starting at level i
                for (let c = 0; c < 3; c++) {
                    // Check if we have enough elements at level i to satisfy:
                    // - j elements to complete sequences from i-2
                    // - k elements to continue sequences from i-1
                    // - c elements to start new sequences from i
                    if (j + k + c <= count[i]) {
                        const remaining = count[i] - (j + k + c);
                        const triplets = Math.floor(remaining / 3);
                        
                        // Total groups gained = completed sequences (j) + new triplets formed
                        const gained = j + triplets;

                        if (dp[j][k] + gained > nextDp[k][c]) {
                            nextDp[k][c] = dp[j][k] + gained;
                        }
                    }
                }
            }
        }
        dp = nextDp;
    }

    return dp[0][0];
}

const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

let input = [];
rl.on('line', (line) => {
    if (line.trim() !== '') {
        input.push(line);
    }
    if (input.length === 2) {
        const V = parseInt(input[0].trim(), 10);
        // Robust platform parsing to handle multiple consecutive spaces cleanly
        const contamination_levels = input[1].trim().split(/\s+/).map(Number);
        
        const result = maxMutatedViruses(V, contamination_levels);
        console.log(result);
        rl.close();
    }
});