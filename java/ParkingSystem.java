public class ParkingSystem {
    private String arr[] = new String[10];
    private int Occupied = 0;
    private int Empty = 10;

    public void Park(String CarNumber){
        int firstemptyindex = -1;
        for(int i = 0;i<arr.length;i++){
            if(arr[i]!= null && arr.equals(CarNumber)){
                System.out.println("Duplicate! the car is already pesent");
            }else if(firstemptyindex == -1){
                firstemptyindex = i;
            }
        }
        if(firstemptyindex != -1){
            arr[firstemptyindex] = CarNumber;
        }else{
            System.out.println("Parking slots are full");
        }
    }
    public void Remove(String CarNumber){
        boolean found = false;
        for(int i = 0;i<arr.length;i++){
            if(arr[i] != null && arr.equals(CarNumber)){
                arr[i] = null;
                found = true;
                break;
            }
        }
        if(!found){
            System.out.println("Car not found");
        }
    }
    public int countempty(){
        int count = 0;
        for(int i = 0;i<arr.length;i++){
            if(arr[i] == null){
                count++;
            }
        }
        return count;
    }
    public void displayoccupied(){
        for(int i = 0;i<arr.length;i++){
            if(arr[i] != null){
                System.out.println("slot:"+i+" has "+arr[i]);
            }
        }
    }
    public static void main(String[] args) {
        ParkingSystem mall = new ParkingSystem();

        mall.Park("MN-55");
        mall.Park("XYZ-10");
        mall.Park("MN-55"); 
        
        mall.displayoccupied();
        System.out.println("Empty Slots: " + mall.countempty());

        mall.Remove("XYZ-10");
        mall.displayoccupied();
    }
}