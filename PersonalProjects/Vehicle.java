
/**
 * Vehicle
 * 
 * This class is a template for a vehicle object. It contains all the basic
 * information about a vehicle, as well as some more specific information
 * about the engine and drivetrain.
 * 
 * This class is used in Main.java
 * 
 * @version 0.0.1
 */
public class Vehicle {
    
    // Basics
    private int year;
    private int seats;
    private String make;
    private String model;
    boolean fixedPlacement;
  
    // Constructors
    Vehicle() {
        // Dont use an empty constructor
        System.out.println("Please do not use an empty constructor.");
        throw new NoSuchMethodError();
    }

    /**
     * Vehicle
     * 
     * This constructor is used to create a vehicle object with all the
     * information about the vehicle.
     */
    Vehicle(int Year, String Make, String Model, int Seats, boolean FixedPlacement) {
        year = Year;
        seats = Seats;
        make = new String(Make.toUpperCase());
        model = new String(Model.toUpperCase());
        fixedPlacement = FixedPlacement;
    }

    Vehicle(int Year, String Make, String Model) {
        year = Year;
        seats = 0;
        make = new String(Make);
        model = new String(Model);
        fixedPlacement = false;
    }

    // Variable Getters
    public int getYear() { return year; }
    public String getMake() { return make; }
    public String getModel() { return model; }
    public int getSeats() { return seats; }
    public boolean getFixedPlacement() { return fixedPlacement; }

    // Variable Setters
    public void setYear(int n) { year = n; }
    public void setMake(String s) { make = new String(s); }
    public void setModel(String s) { model = new String(s); }
    public void setSeats(int n) { seats = n; }
    public void setFixedPlacement(boolean b) { fixedPlacement = b; }
    
    @Override
    public String toString() {
      return year + " " + make + " " + model + " with " + seats + " seats.";
    }
}
