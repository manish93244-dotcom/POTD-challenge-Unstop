import java.io.*;
import java.util.*;

class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(br.readLine().trim());
        Queue<Long> queue = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            String line = br.readLine().trim();

            if (line.startsWith("ENTER")) {
                String[] parts = line.split("\\s+");
                long x = Long.parseLong(parts[1]);
                queue.offer(x);
            } else if (line.equals("EXIT")) {
                if (!queue.isEmpty()) {
                    queue.poll();
                }
            }
        }

        if (queue.isEmpty()) {
            System.out.print("EMPTY");
        } else {
            System.out.print(queue.peek());
        }
    }
}