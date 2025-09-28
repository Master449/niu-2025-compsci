import java.util.Random;

public class Main {
    public static void main(String[] args) {
        Vehicle Car1 = new Vehicle(2000, "Toyota", "Camry", "FWD", "gas", 133, 149, "Inline", 15, 4, 2.2, 130000, 4);
        Vehicle Car2 = new Vehicle(1995, "AM General", "Hummer", "RWD", "DIESEL", 170, 290, "V", 20, 6, 6.5, 250000, 4);
        Car2.setMilesPerGallon(6);

        printAll(Car1);

        Car1.setHorsepower(0);
        Car1.setPistons(0);
        Car1.setTorque(0);
        Car1.setYear(0);
        Car1.setWheels(0);
        Car1.setMilage(0);
        Car1.setMilesPerGallon(0);
        Car1.setFuelTankSize(0);
        Car1.setDisplacement(0);
        Car1.setDriveLayout("");
        Car1.setMake("");
        Car1.setModel("");
        Car1.setFuelType("");
        Car1.setEngineType("");

        Car1.setEngine(0, "", 0, 0, 0);

        printAll(Car1);

        Random rand = new Random();

        while (true) {
            Car2.setYear(rand.nextInt(100) + 1900);
            Car2.setDisplacement(rand.nextDouble() * 10);
            Car2.setMilage(rand.nextDouble() * 100000);
            Car2.setMilesPerGallon(rand.nextDouble() * 10);
            Car2.setFuelTankSize(rand.nextDouble() * 10);
            Car2.setHorsepower(rand.nextInt(1000));
            Car2.setPistons(rand.nextInt(10));
            Car2.setTorque(rand.nextInt(1000));
            System.out.print("\033[H\033[2J");  
            System.out.flush();
            Car2.printVerboseInfo();
        }
    }
    
    static void printAll(Vehicle c) {
        System.out.println(c.getHorsepower());
        System.out.println(c.getPistons());
        System.out.println(c.getTorque());
        System.out.println(c.getYear());
        System.out.println(c.getWheels());
        System.out.println(c.getMilage());
        System.out.println(c.getFuelUsedLifetime());
        System.out.println(c.getDisplacement());
        System.out.println(c.getDriveLayout());
        System.out.println(c.getMake());
        System.out.println(c.getModel());
        System.out.println(c.getFuelType());
        System.out.println(c.getEngineType());
        System.out.println(c.getFuelUsedLifetime());
    }
}
