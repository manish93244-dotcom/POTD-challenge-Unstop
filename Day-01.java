import java.util.*;
import java.math.BigInteger;

class ListNode {
    int val;
    ListNode next;
    ListNode(int x) { val = x; next = null; }
}

public class Main {
    public static String userLogic(ListNode head) {
        if (head == null) {
            return "even";
        }

        // Step 1: Concatenate all numbers sequentially into a string builder
        StringBuilder sb = new StringBuilder();
        ListNode temp = head;
        while (temp != null) {
            sb.append(temp.val);
            temp = temp.next;
        }

        // Remove any unintentional minus signs if negative numbers exist
        String cleanStr = sb.toString().replace("-", "");
        if (cleanStr.isEmpty()) {
            return "even";
        }

        // Step 2: Convert to BigInteger to naturally drop any leading zeros!
        // e.g., "012" automatically becomes the true numerical value 12
        BigInteger originalNum = new BigInteger(cleanStr);
        String nonZeroStr = originalNum.toString();

        // Step 3: Reverse the true numerical string representation
        String reversedStr = new StringBuilder(nonZeroStr).reverse().toString();
        BigInteger reversedNum = new BigInteger(reversedStr);

        // Step 4: Calculate the sum of the digits from the true string representation
        long digitSum = 0;
        for (int i = 0; i < reversedStr.length(); i++) {
            digitSum += Character.getNumericValue(reversedStr.charAt(i));
        }

        // Step 5: Perform the exact math operation: Reverse - Sum
        BigInteger finalResult = reversedNum.subtract(BigInteger.valueOf(digitSum));

        // Step 6: Check if the final resulting number is even or odd
        if (finalResult.mod(BigInteger.valueOf(2)).equals(BigInteger.ZERO)) {
            return "even";
        } else {
            return "odd";
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        if (!sc.hasNextInt()) return;
        
        int N = sc.nextInt();
        ListNode head = null;
        ListNode tail = null;
        
        for (int i = 0; i < N; i++) {
            if (!sc.hasNextInt()) break;
            int value = sc.nextInt();
            ListNode newNode = new ListNode(value);
            if (head == null) {
                head = newNode;
            } else {
                tail.next = newNode;
            }
            tail = newNode;
        }
        
        String result = userLogic(head);
        System.out.println(result);
        sc.close();
    }
}
