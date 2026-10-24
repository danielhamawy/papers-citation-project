import java.util.Scanner;

public class ClassRoom {
    public static void main(String[] args){
        Scanner input = new Scanner(System.in);
        int [][] classroom = new int[3][4];
        int OccupiedSeats = 0;
        int EmptySeats = 0;
        for(int i = 0;i<3;i++){
            for(int j = 0;j<4;j++){
                System.out.print("Enter seat at Row " + i + " Column " + j + " (1 for occupied, 0 for empty): ");
                classroom[i][j] = input.nextInt();
            }
        }
        for(int i = 0;i<3;i++){
            for(int j = 0;j<4;j++){
                System.out.print(classroom[i][j]+" ");
                if(classroom[i][j] == 1){
                    OccupiedSeats++;
                }else{
                    EmptySeats++;
                }
            }
            System.out.println();
        }
        System.out.println("Occupied seats: " + OccupiedSeats);
        System.out.println("Empty seats: " + EmptySeats);
        if(OccupiedSeats>9){
            System.out.println("Almost Full");
        }else if(OccupiedSeats>=5 && OccupiedSeats<=9){
            System.out.println("moderetly occupied");
        }else{
            System.out.println("mostly empty");
        }
        input.close();
    }
}
