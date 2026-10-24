abstract class Staff{
    String name;
    Staff(String name){
        this.name = name;
    }
    abstract void PerformDuty();
}
class Doctor extends Staff{
    Doctor(String name){
        super(name);
    }
    @Override
    void PerformDuty(){
        System.out.println("Doctor: "+name+" is Replacing Damaged heart");
    }
}
class Nurse extends Staff{
    Nurse (String name){
        super(name);
    }
    @Override
    void PerformDuty(){
        System.out.println("Nurse:"+name+" Is monitoring the heart");
    }
}
public class HospitalSystem{
    public static void main(String[] args){
        Staff s1 = new Doctor("Danny Ramy");
        Staff s2 = new Nurse("Hana Ahmed");
        s1.PerformDuty();
        s2.PerformDuty();
    }
}