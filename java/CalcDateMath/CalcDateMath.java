import java.time.LocalDate;
import java.time.Period;
import java.time.Month;


/**
 * public class CalcDateMath
 */
public class CalcDateMath {

    /**
     * public static String getDateDiff(LocalDate dob, LocalDate date)
     */
    public static String getDateDiff(LocalDate startDate, LocalDate endDate) {
        Period period = Period.between(startDate, endDate);
        return "" + period.getYears() + " years" 
        + " and " + period.getMonths() + " months" 
        + " and " + period.getDays() + " days";
    }


    /**
    * public static void main (String[] args)
    */
    public static void main (String[] args) {
        CalcDateMath dm = new CalcDateMath();
        LocalDate currentDate = LocalDate.now();
        LocalDate startDate, endDate;

        startDate = LocalDate.of(2004, Month.JANUARY, 4);
        endDate = LocalDate.of(2010, Month.MARCH, 22);
        System.out.println("Spirit Rover: Start Date = " + startDate.toString() + ":End Date = " + endDate.toString() + ":Length of time = " + dm.getDateDiff(startDate, endDate) + "\n");

        startDate = LocalDate.of(2004, Month.JANUARY, 25);
        endDate = LocalDate.of(2018, Month.JUNE, 10);
        System.out.println("Opportunity Rover: Start Date = " + startDate.toString() + ":End Date = " + endDate.toString() + ":Length of time = " + dm.getDateDiff(startDate, endDate) + "\n");

        return;
    }

}

