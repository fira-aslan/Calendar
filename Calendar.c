#include<stdio.h>
#include<math.h>

const char month_str[13][4] = {
"", "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
"JUL", "AGO", "SEP", "OCT", "NOV", "DEC"
};

int days_in_months[13] = {
0, 31, 28, 31, 30, 31, 30,
31, 31, 30, 31, 30, 31
};

int find_weekday(int month, int year, int day);
int last_two_digs(int Y);
int first_two_digs(int Y);
int check_leap(int Y);
int shift_month(int M);
void print_calendar(int month, int year);

int main(){
    int mm, yy;
    printf("* * *\nEnter the month and the year to create the calendar: ");
    scanf("%d%*c%d", &mm, &yy);
    printf("\n       * * * Here is your calendar * * *\n\n");
    check_leap(yy);
    print_calendar(mm, yy);
    puts("");
    return 0;
}

int find_weekday(int month, int year, int day){
    int Y, y, c, d, m, w;
    if(month == 1 || month ==2) Y = year - 1;
    else Y = year;
    d = day;
    m = shift_month(month); y = last_two_digs(year); c = first_two_digs(year);
    w = (d + (int) floor(2.6*m-0.2) + y + (int) floor(0.25*y) + (int) floor(0.25*c) - 2*c) % 7;
    if(month==1 || month==2){
        if(check_leap(year) == 1){
            w = w - 2;
        }
        else w = w - 1;
    }
    if(w<0) w+=7;
    return w;
}

int last_two_digs(int Y){
    int last = Y % 100;
    return last;
}

int first_two_digs(int Y){
    int first = Y;
    while(first >= 100){
        first = first/10;
    }
    return first;
}

int check_leap(int Y){

    if(Y%4 != 0) return 0;

    else if(Y%100 != 0){
        days_in_months[2] = 29;
        return 1;
    } 

    else if(Y%400 != 0) return 0;
    
    else{
        days_in_months[2] = 29;
        return 1;
    } 
}

int shift_month(int M){
    int m;
    if(M==1 || M==2){
        m = M + 10;
        return m;
    }
    else{
        m = M - 2;
        return m;
    }
}

void print_calendar(int month, int year){
    int day;
    printf("===================================================\n");
    printf("                      %s/%d                        \n", month_str[month], year);
    puts("");
    printf("SUN     MON     TUE     WED     THU     FRI     SAT\n");
    for (day = 1; day <= find_weekday(month, year, 1); day++)
	{
			printf("--      ");
	}
    
    for (day = 1; day <= days_in_months[month]; day++ )
		{
			printf("%02d", day);
			if (find_weekday(month, year, day + 1) > find_weekday(month, year, day))
				printf("      ");
			else
				printf("\n");
		}
    if(find_weekday(month, year, day) != 0){
        for(int i=find_weekday(month, year, day); i<= 6; i++){
        printf("--      ");
        }
        puts("");
    }
    printf("===================================================\n");
}