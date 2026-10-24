public class bankaccount {
    private  String accountholder;
    private double balance;

    public void setaccountholder(String accountholder){
        this.accountholder = accountholder;
    }
    public String getaccountholder(){
        return accountholder;
    }
    public void setbalance(double balance){
        if (balance>=0){
            this.balance = balance;
        }else{
            System.out.println("cant be negative");
        }
    }
    public double getbalance(){
        return balance;
    }
    public static void main(String[] args){
        bankaccount myacc = new bankaccount();
        myacc.setaccountholder("Danny");
        myacc.setbalance(500);
        System.out.println("name: "+myacc.getaccountholder()+" balance: "+myacc.getbalance());
    }
}
