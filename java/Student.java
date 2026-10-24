public class Student {
    private String name;
    private int id;
    private double[] scores;

    public Student(String name,int id,double[] scores){
        this.name = name;
        this.id = id;
        this.scores = scores;
    }
    public double CalculateAvg(){
        double Total = 0;
        for (int i = 0;i<scores.length;i++){
            Total += scores[i];
        }
        return Total/scores.length;
    }
    public String CalculateGrade(){
        double avg = CalculateAvg();
        if(avg>90){
            return "A";
        }else if(avg>50 && avg<=90){
            return "B";
        }else
            return "F";
    }
    public void DisplayStudent(){
        System.out.println("Name: "+name+" ID: "+id+" Average: "+CalculateAvg()+" Grade: "+CalculateGrade());
    }
    public static void main(String[] args){
        double[] s1scores = {10.0,30.0,40.0};
        Student s1 = new Student("Danny",0022,s1scores);
        double[] s2Scores = {40.0, 55.0, 30.0};
        Student s2 = new Student("Alex", 102, s2Scores);
        s1.DisplayStudent();
        s2.DisplayStudent();
    }
}
