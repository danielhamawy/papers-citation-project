public class DiscountCalculator {

    public double calculateDiscount(double price) {
        return price * 0.05;
    }

    public double calculateDiscount(double price, double percentage) {
        return price * (percentage / 100);
    }

    public double calculateDiscount(double price, String customerType) {
        if (customerType == "student") {
            return price * 0.15;
        } else if (customerType == "member") {
            return price * 0.10;
        } else if (customerType == "guest") {
            return price * 0.02;
        }
        return 0;
    }

    public static void main(String[] args) {
        DiscountCalculator dc = new DiscountCalculator();
        double BasePrice = 100.0;

        double d1 = dc.calculateDiscount(BasePrice);
        double d2 = dc.calculateDiscount(BasePrice, 20.0);
        double d3 = dc.calculateDiscount(BasePrice, "student");

        printDetails(BasePrice, d1, "Flat 5%");
        printDetails(BasePrice, d2, "Custom 20%");
        printDetails(BasePrice, d3, "Student Type");

        double finalD1 = BasePrice - d1;
        double finalD2 = BasePrice - d2;
        double finalD3 = BasePrice - d3;

        double lowest;

        if (finalD1 <= finalD2 && finalD1 <= finalD3) {
            lowest = finalD1;
        } else if (finalD2 <= finalD1 && finalD2 <= finalD3) {
            lowest = finalD2;
        } else {
            lowest = finalD3;
        }
        System.out.println("The lowest final price is: " + lowest);
    }

    public static void printDetails(double price, double discount, String label) {
        System.out.println("Original Price: " + price + " Discount: " + discount + " Final: " + (price - discount));
    }
}