public class CustomerBills {
    private String name;
    private int Id;
    private double UnitsConsumed;
    public CustomerBills(String name,int Id,double UnitsConsumed){
        this.name = name;
        this.Id = Id;
        this.UnitsConsumed = UnitsConsumed;
    }
    public double CalculateBill(){
        double Bills = 0;
        if(UnitsConsumed<=100){
            Bills = UnitsConsumed*0.5;
        }else if(UnitsConsumed>100 && UnitsConsumed<=200){
            Bills = (100*0.5)+((UnitsConsumed-100)*0.75);
        }else if(UnitsConsumed>200){
            Bills = (100 * 0.5) + (100 * 0.75) + ((UnitsConsumed - 200) * 1.2);;
        }
        if(Bills>300){
            Bills += Bills*0.1;
        }
        return Bills;
    }
    public void DisplayBills(){
        System.out.println("Name: "+name+" Id: "+Id+" Bills: "+CalculateBill());
    }
    public static void main(String[] args){
        CustomerBills c1 = new CustomerBills("Danny",2008,167);
        CustomerBills c2 = new CustomerBills("Mark",1069,452);
        CustomerBills c3 = new CustomerBills("Omar",34,201);
        double c1bills = c1.CalculateBill();
        double c2bills = c2.CalculateBill();
        double c3bills = c3.CalculateBill();
        if(c1bills>c2bills && c1bills>c3bills){
            System.out.println("Danny has the most Bills to pay");
        }else if(c2bills>c1bills && c2bills>c3bills){
            System.out.println("Mark has the most Bills to pay");
        }else{
            System.out.println("Omar has the most Bills to pay");
        }

    }
}
