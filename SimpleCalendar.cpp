#include <iostream>
using namespace std;

int requestStartYear();
int requestEndYear(int startYear);
char chooseFirstWeekday();
int calculateYearStartWeekday(int count, int startYear);
void printCalendar(char months[12][3], char days[7][1], int numberOfDaysInMonth[],int startYear, int endYear, int count);

int main(){
    char redo = 'n';
    do{
        char months[12][3] = {{'J','a','n'},{'F','e','b'}, {'M','a','r'},{'A','p','r'},{'M','a','y'},{'J','u','n'},{'J','u','l'},{'A','u','g'},{'S','e','p'},{'O','c','t'},{'N','o','v'},{'D','e','c'}};
        char days[7][1] = {{'M'},{'T'},{'W'},{'T'},{'F'},{'S'},{'S'}};
        int numberOfDaysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        int count = -1;//Keeps track of what weekday we're at. Value allows for adjusting of calendar start weekday value. 1900-01-01 was a Monday(-1)
        int startYear, endYear;
        char weekdayResponse;
        
        //Let the user choose the year the calendar starts from and ends at
        startYear = requestStartYear();
        endYear = requestEndYear(startYear);
        //Give the user the option to choose Sunday as first day of the weekday
        weekdayResponse = chooseFirstWeekday();
        if (weekdayResponse == 'y' || weekdayResponse == 'Y'){
            days[0][0]='S',days[1][0]='M',days[2][0]='T',days[3][0]='W',days[4][0]='T',days[5][0]='F',days[6][0]='S';
            count+=1;
        }
        //Calculate to find the weekday at which the year is to start at
        count = calculateYearStartWeekday(count, startYear);
        //Print the calendar
        printCalendar(months, days, numberOfDaysInMonth, startYear, endYear, count);
        
        cout<<endl<<"Do you want to use the calendar again?: ";
        cin>>redo;
    } while(redo=='y' || redo=='Y');

    return 0;
}

int requestStartYear(){
    int startYear;
    cout<<"What year do you want the calendar to start from?: ";
    cin>>startYear;
    for (;;){
        if(startYear<1900){
            cout<<"Please choose a year greater than or equal to 1900"<<endl
                <<"What year do you want the calendar to start from?: ";
            cin>>startYear;
        }else{
            break;
        }
    }
    
    return startYear;
}

int requestEndYear(int startYear){
    int endYear;
    cout<<"What year do you want the calendar to end at?: ";
    cin>>endYear;
    for (;;){
        if((endYear>2099) || (endYear<startYear)){
            cout<<"Please choose a year that is equal to or greater than the start year but less than 2100"<<endl
                <<"What year do you want the calendar to end at?: ";
            cin>>endYear;
        } else {
            break;
        }
    }
    
    return endYear;
}

char chooseFirstWeekday(){
    char response;
    cout<<"Do you wish to choose Sunday as the first day of the week?(y/n): ";
    cin>>response;
    
    return response;
}

int calculateYearStartWeekday(int count, int startYear){
     //Automatically pick start date depending on the year chosen knowing 1900-01-01 was a Monday(-1)
    int yearsDifference = startYear - 1900;
    //Find number of leap years in the difference
    int numberOfLeapYears = yearsDifference / 4;
    int numberOfWeekdayNameShifts=((yearsDifference - numberOfLeapYears) + (numberOfLeapYears * 2))%7;
    //Adjust numberOfWeekdayNameShifts if startYear is a leap year to prevent an extra day being added to the start date
    if(startYear%4 == 0){
        numberOfWeekdayNameShifts-=1;
        if((startYear%100==0) && (startYear%400!=0)){
            //This is not a leap year so add the subtracted value back
            numberOfWeekdayNameShifts+=1;
        }
    }
    if(numberOfWeekdayNameShifts + count > 6){
        count=(numberOfWeekdayNameShifts + count) - 7;
    }else{
        count+=numberOfWeekdayNameShifts;
    }
    
    return count;
}

void printCalendar(char months[12][3], char days[7][1], int numberOfDaysInMonth[], int startYear, int endYear, int count){
    cout<<endl<<"********** Calendar for "<<startYear<<" to "<<endYear<<" **********"<<endl<<endl;
    int testCount;
    for (int i=startYear; i<endYear+1; i++){
        //Years 
        cout<<endl<<"******************** "<<i<<" ********************"<<endl;
        //Check whether it's a leap year to adjust number of days in Feb
        if(i%4 == 0){
            numberOfDaysInMonth[1] = 29;
            //If a year is divisible by 100, it should also be divisible by 400 to be a leap year
            if((i%100 == 0) && (i%400 != 0)){
                numberOfDaysInMonth[1] = 28;
            }
        }else{
            numberOfDaysInMonth[1] = 28;
        }
        for (int j=0; j<12; j++){
            //Months
            cout<<months[j][0]<<months[j][1]<<months[j][2]<<" "<<i<<endl;
            for (int k=0; k<7; k++){
                //List days of the week names
                cout<<days[k][0]<<"\t";
            }
            cout<<endl;
            for (int m=0; m<count+1; m++){
                //Find out what weekday name we're at to start listing days of that month from there
                cout<<"\t";
            }
            int days = 0;
            for (int l=0; l<numberOfDaysInMonth[j]; l++){
                //List days numbers
                days+=1;
                count+=1;
                if(count>6){
                    //If day of the week is past seven, go back to first week day name
                    cout<<endl;
                    count=0;
                }
                cout<<days<<"\t";
            }
            cout<<endl;
        }
    }
}
