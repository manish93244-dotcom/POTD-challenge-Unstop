function isPrime(num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 === 0 || num % 3 === 0) return false;
    for (let i = 5; i * i <= num; i += 6) {
        if (num % i === 0 || num % (i + 2) === 0) return false;
    }
    return true;
}

function talentBurst(arr) {
    const n = arr.length;
    
    // Pad the array with 1 at both boundaries to represent implicit edge neighbors
    const A = [1, ...arr, 1];
    const m = A.length;

    // dp[i][j] stores the maximum score by removing all elements in open interval (i, j)
    const dp = Array.from({ length: m }, () => new Array(m).fill(0));

    // length is the distance between i and j
    for (let len = 2; len < m; len++) {
        for (let i = 0; i < m - len; i++) {
            const j = i + len;
            
            // Find the optimal last element k to remove in the interval (i, j)
            for (let k = i + 1; k < j; k++) {
                const baseScore = (A[i] + 2) * A[k] * (A[j] + 2);
                const bonus = isPrime(A[k]) ? A[k] : 0;
                const totalScore = baseScore + bonus;
                
                const currentScore = totalScore + dp[i][k] + dp[k][j];
                if (currentScore > dp[i][j]) {
                    dp[i][j] = currentScore;
                }
            }
        }
    }

    // The answer is the max score for the entire open interval spanning from 0 to m-1
    return dp[0][m - 1];
}

function main() {
    const fs = require('fs');
    const input = fs.readFileSync('/dev/stdin', 'utf8');
    const data = input.trim().split(/\s+/);
    
    if (data.length < 1 || data[0] === "") return;
    
    const n = parseInt(data[0], 10);  
    const arr = data.slice(1, n + 1).map(Number);  
    
    const result = talentBurst(arr);
    console.log(result);
}

main();
