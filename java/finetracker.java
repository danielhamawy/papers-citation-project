import java.util.Scanner;

public class finetracker{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.println("name: ");
        String name = sc.nextLine();
        System.out.println("late days: ");
        int days = sc.nextInt();
        double totalfine = calculatefine(days);
        System.out.println("name "+name+" total fine "+totalfine);
        sc.close();
    }
    public static double calculatefine(int latedays){
        double fine = 0;
        if (latedays<= 5){
            fine = latedays*1.0;
        }else{
            fine = (5*1.0)+((latedays-5)*2.0);
        }
        return fine;
    }
}