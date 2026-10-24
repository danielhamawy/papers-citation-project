public class Incident {
    private String IncidentType;
    private int InjuredPeople;
    private boolean Fire;
    private boolean RoadBlocked;
    public Incident(String IncidentType,int InjuredPeople,boolean Fire,boolean RoadBlocked){
        this.IncidentType = IncidentType;
        this.InjuredPeople = InjuredPeople;
        this.Fire = Fire;
        this.RoadBlocked = RoadBlocked;
    }
    public String GetSeverityLevel(){
        if(InjuredPeople>5 && Fire == true){
            return "Critical";
        }else if(InjuredPeople>=1 && InjuredPeople<=5 || RoadBlocked == true){
            return"High";
        }else if(InjuredPeople == 0 && Fire == true){
            return"Moderate";
        }else{
            return"Low";
        }
    }
    public static void main(String[] args) {
        Incident[] reports = {
            new Incident("Factory Explosion", 10, true, true),
            new Incident("Car Crash", 2, false, true),
            new Incident("Small Kitchen Fire", 0, true, false),
            new Incident("Cat in Tree", 0, false, false),
            new Incident("Chemical Spill", 7, true, false)
        };
        int countcritical = 0;
        for(int i = 0;i<reports.length;i++){
            String severity = reports[i].GetSeverityLevel();
            System.out.println("Incident: "+reports[i].IncidentType+" Severity: "+reports[i].GetSeverityLevel());
            if(severity.equals("Critical")){
                countcritical++;
            }
        }
        System.out.println("Total critical incidnts: "+countcritical);
}
}