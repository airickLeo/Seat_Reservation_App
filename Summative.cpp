#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

double **readSeatPrices(int numRows, int evenCol, int oddCol)
{
    /*This function takes in as parameters the total number of rows in the
    auditorium, the number of columns for even rows, and the number of columns
    for odd rows, and returns a local double 2D Dynamic array "seatPrices" */

    //Declares a 2D Dynamic array of 15 rows of type double
    double **seatPrices = new double*[numRows];

    //For loop that creates a 2D dynamic jagged array that has different number of columns per row
    for(int row = 0; row < numRows; row++)
    {
        if(row % 2 != 0)
            seatPrices[row] = new double[oddCol];

        else
            seatPrices[row] = new double[evenCol];
    }//end for

    ifstream fin;
    fin.open("prices.txt");

    //for loops that stores the input from file "prices.txt" into the 2D dynamic jagged array
    for(int row = 0; row < numRows; row++)
    {
        //stores prices into the odd rows of the 2d dynamic jagged array
        if(row % 2 != 0)
        {
            for(int col = 0; col < oddCol; col++)
            {
                fin >> seatPrices[row][col];
            }//end for
        }//end if
        //stores prices into the even rows of the 2d dynamic jagged array
        else
        {
            for(int col = 0; col < evenCol; col++)
            {
                fin >> seatPrices[row][col];
            }//end for
        }//end else
    }//end for
    return seatPrices;
}//end **readSeatPrices()

char **readSeats(int numRows, int evenCol, int oddCol)
{
    /* This function takes in as parameters the rows in the
    auditorium, the number of columns for even rows, and the number of columns
    for odd rows, and returns a local character 2D Dynamic array "availableSeats" */

    //declares a 2d dynamic array of type char of 15 rows
    char **availableSeats = new char*[numRows];

    //For loop that creates a 2D dynamic jagged array that has different number of columns per row
    for(int row = 0; row < numRows; row++)
    {
        if(row % 2 != 0)
            availableSeats[row] = new char[oddCol];

        else
            availableSeats[row] = new char[evenCol];
    }//end for

    fstream fin;
    fin.open("seats.txt");

    //for loops that stores the input from file "prices.txt" into the 2D dynamic jagged array
    for(int row = 0; row < numRows; row++)
    {
        //stores prices into the odd rows of the 2d dynamic jagged array
        if(row % 2 != 0)
        {
            for(int col = 0; col < oddCol; col++)
            {
                fin >> availableSeats[row][col];
            }//end for
        }//end if
        //stores prices into the even rows of the 2d dynamic jagged array
        else
        {
            for(int col = 0; col < evenCol; col++)
            {
                fin >> availableSeats[row][col];
            }//end for
        }//end else
    }//end overall for
    fin.close();
    return availableSeats;
}//end **readSeats()

void displaySeats(char **seats, int numRows, int evenCol, int oddCol)
{
    /*This function takes in as parameters the 2d dynamic array "seats", the
    total number of rows in the  auditorium, the number of columns for even rows,
    and the number of columns for odd rows, and displays the seating chart */

    //prints the seat numbers
    cout << "\n\n  " << "Seats are available if marked as '#', and taken if marked as 'X'" << endl;
    cout << endl;

    cout << setw(42) << "Seating Chart" << endl;
    cout << "\n" << setw(6) << " ";
    //for loop that displays the column(seat) number at the top of the chart
    for(int col = 0; col < evenCol; col++)
    {
        cout << setw(3) << col;
    }//end for
    cout << endl;

    //for loop that displays the availability of the chart
    for(int row = 0; row < numRows; row++)
    {
        cout << "\nRow" << row << right;
        //if and else statements that help line up the columns in the chart
        if(row >= 10)
            cout << setw(3) << " ";

        else
            cout << setw(4) << " ";

        //prints the availability of even rows
        if(row % 2 == 0)
        {
            //for loop that prints availability of the 20 seats in an even row
            for(int col = 0; col < evenCol; col++)
                cout << seats[row][col] << setw(3);

            cout << endl;
        }//end if
        //prints the availability of odd rows
        else
        {
            //for loop that prints availability of the 15 seats in an odd row
            for(int col = 0; col < oddCol; col++)
                cout << seats[row][col] << setw(3);

            cout << endl;
        }//end else
    }//end chart displaying for loop
}//end displaySeats()

bool priceAndChartUpadate(char **seats, double **prices, int numRows, int evenCol, int oddCol, int &totalPurchases, double &totalSales)
{
    /*This function displays the price of seats and updates the chart when a sale is made. This function
    takes in as parameters the 2d dynamic arrays "seats" and "prices", total number
    of rows in the auditorium, the number of columns for even and odd rows. This function also takes in
    two reference variables "oddCol" and "totalSales" */

    int amountOfPurchases;
    cout << "\n\nHow many seats would you like to purchase? ";
    cin >> amountOfPurchases;

    int numOfPurchasedSeats = 0;
    //while loop that would keep iterating to record the spots the user bought and updates the chart
    //when after sale
    while(numOfPurchasedSeats < amountOfPurchases)
    {
        int rowNum, seatNum;
        displaySeats(seats, numRows, evenCol, oddCol);
        cout << "\nPlease input the row number: ";
        cin >> rowNum;

        //while loop that sets input validation for rows
        while(rowNum > 14 || rowNum < 0)
        {
            cout << "\nThis row does not exist, please re-enter: ";
            cin >> rowNum;
        }//end while

        cout << "\nPlease input the seat number: ";
        cin >> seatNum;
        //if statement and while loop that works together to set input validation for column #
        //in even rows
        if(rowNum % 2 == 0)
        {
            while(seatNum > evenCol || seatNum < 0)
            {
                cout << "\nThis seat number does not exist, please re-enter: ";
                cin >> seatNum;
            }//end while
        }//end if

        //else if statement and while loop that works together to set input validation for column #
        //in odd rows
        else if(rowNum % 2 != 0)
        {
            while(seatNum > oddCol || seatNum < 0)
            {
                cout << "\nThis seat number does not exist, please re-enter: ";
                cin >> seatNum;
            }//end while
        }//end else if

        //while loop that keeps iterating to ask user to re-enter if the seat is taken
        while(seats[rowNum][seatNum] == 'X')
        {
            cout << "This seat is already taken, please choose another seat" << endl;
            cout << "\nPlease enter the row number: ";
            cin >> rowNum;
            while(rowNum > 14 || rowNum < 0)
            {
                cout << "\nThis row does not exist, please re-enter: ";
                cin >> rowNum;
            }//end while
            cout << "\nPlease enter the seat number: ";
            cin >> seatNum;
            if(rowNum % 2 == 0)
            {
                while(seatNum > evenCol || seatNum < 0)
                {
                    cout << "\nThis seat number does not exist, please re-enter: ";
                    cin >> seatNum;
                }//end while
            }//end if

            //else if statement and while loop that works together to set input validation for column #
            //in odd rows
            else if(rowNum % 2 != 0)
            {
                while(seatNum > oddCol || seatNum < 0)
                {
                    cout << "\nThis seat number does not exist, please re-enter: ";
                    cin >> seatNum;
                }//end while
            }//end else if

        }//end while

        //if statement that updates the chart and displays the price of the seat chosen
        if(seats[rowNum][seatNum] == '#')
        {
            cout << "\nThe price of this seat is: $" << fixed << setprecision(2) << prices[rowNum][seatNum];
            seats[rowNum][seatNum] = 'X';
            totalSales += prices[rowNum][seatNum];
        }//end if
        cout << endl;
        numOfPurchasedSeats++;
        totalPurchases++;
    }

    string choice;
    cout << "\nWould you like to purchase more seats? (type yes or no): ";
    cin >> choice;

    //if statement that returns true if the users wants to buy more tickets
    if(choice == "yes")
        return true;
    //else statement that returns false if the user doesn't
    else
        return false;
}

int main()
{
    //Create 2D dynamic arrays
    const int numRows = 15;
    const int oddCol = 15;
    const int evenCol = 20;
    bool option = true;
    int totalPurchases = 0;
    double totalSales = 0;
    int availableSeats = 0;

    //declares a 2d dynamic array to store the values kept within the double type
    // 2d dynamic array previously returned
    double **prices = readSeatPrices(numRows, evenCol, oddCol);

    //declares a 2d dynamic array to store the values kept within the char type
    // 2d dynamic array previously returned
    char **seats = readSeats(numRows, evenCol, oddCol);

    cout << "                 " << "Welcome to School Without Walls!";

    //while loop that keeps iterating to call the priceAndChartUpdate function to allow user
    //to buy more tickets until user says "no"
    while(option)
    {
        option = priceAndChartUpadate(seats, prices, numRows, evenCol, oddCol, totalPurchases, totalSales);
    }//end while

    cout << "\n\n*****************************************" << endl
         << "****             Results             ****" << endl
         << "*****************************************" << endl;

    cout << "\nTotal dollar amount of tickets: $";
    cout << fixed << setprecision(2) << totalSales << endl;
    cout << "Total number of seats sold: " << totalPurchases << endl;

    //for loop that counts the total available seats
    for(int row = 0; row < numRows; row++)
    {
        //if statement and for loop that works together to keep track of the available seats in odd rows
        if(row % 2 != 0)
        {
            for(int col = 0; col < oddCol; col++)
            {
                if(seats[row][col] == '#')
                    availableSeats++;
            }//end for
        }//end if

        //if statement and for loop that works together to keep track of the available seats in odd rows
        else
        {
            for(int col = 0; col < evenCol; col++)
            {
                if(seats[row][col] == '#')
                    availableSeats++;
            }//end for
        }//end else
    }//end overall for loop

    cout << "Total number of available seats: " << availableSeats << endl;
    cout << "\nThank you for buying tickets for the play at School Without Walls!" << endl;
    cout << "\nPlease enjoy the show!" << endl;

    return 0;
}

