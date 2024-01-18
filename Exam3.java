import javax.swing.*;
//import java.awt.*;

public class Exam3 {
  JFrame f;
  Exam3() {
    f = new JFrame();
    f.setSize(900, 900);
    f.setLayout(null);
    f.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
    f.setVisible(true);
  }

  public static void main(String[] args) {
    System.out.println("Hello world!");
    new Exam3();
//    System.exit();
  }
}
