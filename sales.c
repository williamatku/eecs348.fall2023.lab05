#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
    Dev:            William A. Morris
    Created:        2023-10-12
    Last Modified:  2023-10-13

    KUID:           3057236
    Email:          morris.william@ku.edu
    Class:          EECS 348 
    Lab Section:    Thursdays @11am

    Description:    
        A simple (and probably unsafe) C Program to generate an annual sales report.
*/

// define global constants

// String array to keep names of months
const char* MONTHS[] 
        = {"January", "February", "March",
        "April", "May", "June",
        "July", "August", "September", 
        "October", "November", "December"};

void read_input_file_as_monthly_sales(char* path, double* dest);

void get_months_in_descending_order(double* sales_by_month, int* dest);

void generate_sales_report_and_save(double* sales_ordered_by_month, int* max_to_min_sales_months);

int main(int argc, char** argv) {
    // The user must pass in a file path
    if (argc != 2) return 1; 

    // Var to capture user-provided path
    char path_to_file[100]; 
    // Save the passed in file path
    strcpy (path_to_file, argv[1]); 

    double sales_ordered_by_month[12];
    read_input_file_as_monthly_sales(path_to_file, sales_ordered_by_month);

    // Int[] to store the ORDER of the sales numbers (from max->min) by month. 
    int max_to_min_sales_months[12]; 
    get_months_in_descending_order(sales_ordered_by_month, max_to_min_sales_months);
  
    generate_sales_report_and_save(sales_ordered_by_month, max_to_min_sales_months);

    return 0; // exit wo errors :)
}

void read_input_file_as_monthly_sales(char* path, double* dest) {
    double sales_ordered_by_month[12]; // Double[] to capture sales numbers in order Jan->Dec
    
    FILE* input_file = fopen(path, "r"); // and open requested file

    for (int i = 0; i < 12; i++) { // read 12 lines from the file, corresponding to the sales totals in order by month
        if (!fscanf(input_file, "%lf", &sales_ordered_by_month[i])) exit(-1); // if a line cannot be read as a double, exit the program
    }

    memcpy(dest, sales_ordered_by_month, sizeof(sales_ordered_by_month));
}

void get_months_in_descending_order(double* sales_by_month, int* dest) {
    double sort_buffer[12]; // copy the ordered list to a buffer
    int max_to_min_sales_months[12]; // Int[] to store the ORDER of the sales numbers (from max->min) by month. 

    memcpy (sort_buffer, sales_by_month, sizeof(sort_buffer));

    for (int i = 0; i < 12; i++) { // perform following sort 12 times, for 12 numbers
        int largest_month = 0; // start from january every time
        for (int j = 0; j < 12; j++) {
            // locate the largest remaining month in the set and save 
            if (sort_buffer[largest_month] <= sort_buffer[j]) largest_month = j;
        } 
        sort_buffer[largest_month] = -1; // replace largest number
        max_to_min_sales_months[i] = largest_month; // save the largest located month to appropriate location in memory
    }

    memcpy(dest, max_to_min_sales_months, sizeof(max_to_min_sales_months));
}

void generate_sales_report_and_save(double* sales_ordered_by_month, int* max_to_min_sales_months) {
    FILE* output_file = fopen("./sales_report.txt","w"); // open an output file

    fprintf(output_file, "\nMonthly sales report for 2022: \n\tMONTH\t\tSALES\n");
    for (int i = 0; i < 12; i++) { // print out sales for each month in order by month
        fprintf(output_file, "\t%s\t\t$%.2f\n",
            MONTHS[i],
            sales_ordered_by_month[i]);
    }

    fprintf(output_file, "\nSales summary: \n");
    fprintf(output_file, "\tMinimum sales:\t$%.2f (%s)\n", 
        sales_ordered_by_month[max_to_min_sales_months[11]], // smallest sales month stored last in max->min month array 
        MONTHS[max_to_min_sales_months[11]]); 
    fprintf(output_file, "\tMaximum sales:\t$%.2f (%s)\n", 
        sales_ordered_by_month[max_to_min_sales_months[0]], // max sales month stored first in max->min month array
        MONTHS[max_to_min_sales_months[0]]);

    double total_avg_sales = 0; // add up sales # from every month and divide by 12 to calculate average
    for (int i = 0; i < 12; i++) {
        total_avg_sales += sales_ordered_by_month[i];
    }
    total_avg_sales /= 12;

    fprintf(output_file, "\tAverage sales:\t$%.2f\n", total_avg_sales);
    
    fprintf(output_file, "\nSix-Month Moving Average Report: \n");
    for (int start_month = 0; start_month <= 6; start_month++) {
        int final_month = start_month + 5; 

        // calculate average sales for every 6 month period
        double average_sales = 0;
        for (int k = start_month; k <= final_month; k++) {
            average_sales += sales_ordered_by_month[k];
        }
        average_sales /= 6;

        fprintf(output_file, "\t%s -> %s \t $%.2f\n",
            MONTHS[start_month],
            MONTHS[final_month],
            average_sales); 
    }

    fprintf(output_file, "\nSales Report (Highest to Lowest):\n\tMONTH\t\tSALES\n");
    for (int i = 0; i < 12; i++) {
        // go through max->min array and print out sales figure for every month in order by sales.
        fprintf(output_file, "\t%s\t\t$%.2f\n",
            MONTHS[max_to_min_sales_months[i]], 
            sales_ordered_by_month[max_to_min_sales_months[i]]);
    }
}
