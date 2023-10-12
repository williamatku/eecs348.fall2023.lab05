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

/**
 * function that takes in a path to a sales summary and a destination array
 *  reads the given file into memory
 *  and saves the sales in order by month to provided double[]
*/
void read_input_file_as_monthly_sales(char* path, double* dest);

/**
 * function to take in a double[] of sales ordered by month
 *  rank the months in descending order
 *  and save the descending order of months by sale to int[]
*/
void get_months_in_descending_order(double* sales_by_month, int* dest);

/**
 * function that takes in a double[] of sales ordered by month
 *  AND an int[] array of months ordered by sales in descending order
 *  and creates an output file to save final sales report in
*/
void generate_sales_report_and_save(double* sales_ordered_by_month, int* max_to_min_sales_months);

int main(int argc, char** argv) {
    // The user must pass in a file path, else return error
    if (argc != 2) return 1; 

    // init variable to capture path to input file
    char path_to_file[100]; 
    // and save the file path
    strcpy (path_to_file, argv[1]); 

    // init array to store sales in order by month
    double sales_ordered_by_month[12];
    // call function to populate array
    read_input_file_as_monthly_sales(path_to_file, sales_ordered_by_month);

    // Int[] to store the ORDER of the sales numbers (from max->min) by month. 
    int max_to_min_sales_months[12]; 
    // call function to populate array
    get_months_in_descending_order(sales_ordered_by_month, max_to_min_sales_months);
  
    // now that we have sales by month and months by sale, generate the annual sales report
    generate_sales_report_and_save(sales_ordered_by_month, max_to_min_sales_months);

    // exit wo errors :)
    return 0; 
}

void read_input_file_as_monthly_sales(char* path, double* dest) {    
    // open requested file in READ mode
    FILE* input_file = fopen(path, "r");

    // read 12 lines from the file, corresponding to the sales totals in order by month
    for (int i = 0; i < 12; i++)
        // if a line cannot be read as a double and saved to dest. array
        if (!fscanf(input_file, "%lf", &dest[i])) 
            // exit the program
            exit(-1);
}

void get_months_in_descending_order(double* sales_by_month, int* dest) {
    // create buffer to perform sort operation
    double sort_buffer[12]; 

    // create copy of sales ordered by month and save to buffer
    memcpy (sort_buffer, sales_by_month, sizeof(sort_buffer));

    // perform following sort 12 times, for 12 numbers
    for (int i = 0; i < 12; i++) { 
        // start from january every time
        int largest_month = 0;

        for (int j = 0; j < 12; j++) 
            // locate the largest remaining month in the set and save 
            if (sort_buffer[largest_month] <= sort_buffer[j]) largest_month = j;
        
        // replace the largest number found in current iteration
        sort_buffer[largest_month] = -1; 
        // save the largest located month to appropriate location in memory
        dest[i] = largest_month; 
    }
}

void generate_sales_report_and_save(double* sales_ordered_by_month, int* max_to_min_sales_months) {
    // open an output file in WRITE mode
    FILE* output_file = fopen("./sales_report.txt","w"); 

    fprintf(output_file, "\nMonthly sales report for 2022: \n\tMONTH\t\tSALES\n");

    // print out sales for each month in order by month
    for (int i = 0; i < 12; i++)
        fprintf(output_file, "\t%s\t\t$%.2f\n",MONTHS[i],sales_ordered_by_month[i]);


    fprintf(output_file, "\nSales summary: \n");

    // locate worst month for sales and output
    fprintf(output_file, "\tMinimum sales:\t$%.2f (%s)\n", 
        // smallest sales month stored last in max->min month array 
        sales_ordered_by_month[max_to_min_sales_months[11]], 
        MONTHS[max_to_min_sales_months[11]]); 

    // locate best month for sales and output
    fprintf(output_file, "\tMaximum sales:\t$%.2f (%s)\n", 
        // max sales month stored first in max->min month array
        sales_ordered_by_month[max_to_min_sales_months[0]], 
        MONTHS[max_to_min_sales_months[0]]);

    
    double total_avg_sales = 0; 
    // add up sales # from every month 
    for (int i = 0; i < 12; i++) {
        total_avg_sales += sales_ordered_by_month[i];
    }
    // and divide by 12 to calculate average
    total_avg_sales /= 12;
    // and output
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

    fclose(output_file);
}
