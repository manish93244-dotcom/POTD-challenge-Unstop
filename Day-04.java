import java.util.*;

public class Main {

    public static int findMostFrequent(int[] bookIDs) {
        Map<Integer, Integer> freq = new HashMap<>();

        for (int id : bookIDs) {
            freq.put(id, freq.getOrDefault(id, 0) + 1);
        }

        int maxFreq = 0;
        int smallestId = Integer.MAX_VALUE;

        for (Map.Entry<Integer, Integer> entry : freq.entrySet()) {
            int id = entry.getKey();
            int count = entry.getValue();

            if (count > maxFreq) {
                maxFreq = count;
                smallestId = id;
            } else if (count == maxFreq) {
                if (id < smallestId) {
                    smallestId = id;
                }
            }
        }

        return smallestId;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int N = scanner.nextInt();
        int[] bookIDs = new int[N];

        for (int i = 0; i < N; i++) {
            bookIDs[i] = scanner.nextInt();
        }

        System.out.println(findMostFrequent(bookIDs));

        scanner.close();
    }
}