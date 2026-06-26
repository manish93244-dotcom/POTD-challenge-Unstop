function find_lucky_stone_pairs(p, n, m, stones) {
    let luckyCount = 0;

    // State-first filter: count how many stones satisfy the divisibility rule
    for (let i = 0; i < p; i++) {
        if (stones[i] % n === 0 || stones[i] % m === 0) {
            luckyCount++;
        }
    }

    // Number of unique pairs from luckyCount elements is K * (K - 1) / 2
    if (luckyCount < 2) {
        return 0;
    }
    
    return (luckyCount * (luckyCount - 1)) / 2;
}

function main() {
    const fs = require('fs');
    // Using a robust tokenizer to handle newlines, multiple spaces, and carriage returns safely
    const input = fs.readFileSync(0, 'utf8').trim().split(/\s+/);
    if (input.length < 3 || input[0] === "") return;

    const p = parseInt(input[0], 10);
    const n = parseInt(input[1], 10);
    const m = parseInt(input[2], 10);
    
    // Slice only the valid 'p' elements belonging to the stone values
    const stones = input.slice(3, 3 + p).map(Number);

    const result = find_lucky_stone_pairs(p, n, m, stones);
    console.log(result);
}

main();