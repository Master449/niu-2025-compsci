public class CarDriver {
	public static void main(String[] args) {
		Car car1 = new Car("Subaru", "Forester", 2002, 26.5);
		Car car2 = new Car("Ford", "Focus", 2005, 30.0);
		Car car3 = new Car("Chevrolet", "Silverado", 2010, 18.7);
		Car car4 = new Car("Brad's Cars", 2017 , 30);
		Car car5 = new Car("Chevrolet", "Vega", 1976, 28.2);

		if(car1.isPractical() == true) {
			System.out.println("Brand: " + car1.getBrand() + "\nModel: " + car1.getModelName() + "\nMPG: "  + car1.getMPG() + "\nYear: "  + car1.getYear());
			System.out.println("Practical");
		} else {
			System.out.println("Brand: " + car1.getBrand() + "\nModel: " + car1.getModelName());
			System.out.println("Not Practical");
		}

		if(car2.isPractical() == true) {
			System.out.println("Brand: " + car2.getBrand() + "\nModel: " + car2.getModelName() + "\nMPG: "  + car2.getMPG() + "\nYear: "  + car2.getYear());
			System.out.println("Practical");
		} else {
			System.out.println("Brand: " + car2.getBrand() + "\nModel: " + car2.getModelName());
			System.out.println("Not Practical");
		}

		if(car3.isPractical() == true) {
			System.out.println("Brand: " + car3.getBrand() + "\nModel: " + car3.getModelName() + "\nMPG: "  + car3.getMPG() + "\nYear: "  + car3.getYear());
			System.out.println("Practical");
		} else {
			System.out.println("Brand: " + car3.getBrand() + "\nModel: " + car3.getModelName());
			System.out.println("Not Practical");
		}

		if(car4.isPractical() == true) {
			System.out.println("Brand: " + car4.getBrand() + "\nModel: " + car4.getModelName() + "\nMPG: "  + car4.getMPG() + "\nYear: "  + car4.getYear());
			System.out.println("Practical");
		} else {
			System.out.println("Brand: " + car4.getBrand() + "\nModel: " + car4.getModelName());
			System.out.println("Not Practical");
		}

		if(car5.isPractical() == true) {
			System.out.println("Brand: " + car5.getBrand() + "\nModel: " + car5.getModelName() + "\nMPG: "  + car5.getMPG() + "\nYear: "  + car5.getYear());
			System.out.println("Practical");
		} else {
			System.out.println("Brand: " + car5.getBrand() + "\nModel: " + car5.getModelName());
			System.out.println("Not Practical");
		}
	}
}