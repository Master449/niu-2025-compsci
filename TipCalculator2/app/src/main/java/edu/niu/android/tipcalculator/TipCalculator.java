package edu.niu.android.tipcalculator;

public class TipCalculator
{
    private double tip;
    private double bill;

    public TipCalculator(double tip, double bill)
    {
        setTip(tip);
        setBill(bill);
    }

    public double getTip()
    {
        return tip;
    }

    public double getBill()
    {
        return bill;
    }

    public void setTip(double tip)
    {
        if (tip > 0)
            this.tip = tip;
    }

    public void setBill(double bill)
    {
        if (bill > 0)
            this.bill = bill;
    }

    public double tipAmount()
    {
        return bill * tip;
    }

    public double totalAmount()
    {
        return bill + tipAmount();
    }
}