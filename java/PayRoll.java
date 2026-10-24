abstract class Employees {
    private String name;
    private int id;
    Employees(String name,int id){
        this.name = name;
        this.id = id;
    }
    public String getName() { return name; }
    public int getId() { return id; }
    public abstract double CalculateSalary();
}
class FullTimeEmployees extends Employees{
    private double MonthlySalary;
    private double bonus;
    FullTimeEmployees(String name,int id,double MonthlySalary,double bonus){
        super(name,id);
        this.MonthlySalary = MonthlySalary;
        this.bonus = bonus;
    }
    @Override
    public double CalculateSalary(){
        return MonthlySalary+bonus;
    }
}
class PartTimeEmployees extends Employees{
    private int HoursWorked;
    private double HourlyRate;
    PartTimeEmployees(String name,int id,int HoursWorked,double HourlyRate){
        super(name,id);
        this.HourlyRate = HourlyRate;
        this.HoursWorked = HoursWorked;
    }
    @Override
    public double CalculateSalary(){
        return HourlyRate*HoursWorked;
    }
}
public class PayRoll{
    public static void main(String[] args){
        Employees e1 = new FullTimeEmployees("Danny",222,1000,21);
        Employees e2 = new PartTimeEmployees("Ahmed",42,201,5);
        DisplayInfo(e1);
        DisplayInfo(e2);
    }
    public static void DisplayInfo(Employees e){
        System.out.println("name: "+e.getName()+" ID: "+e.getId()+" Salary: "+e.CalculateSalary());
    }
}