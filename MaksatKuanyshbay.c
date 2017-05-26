#include <stdio.h>

typedef struct {
	int id;   //defining sale_id
	int day;   //day
	int quantity;   //quantity
	char type [20];   //type
	double cost;   //cost of order
	char arrangement [20];   //arrangement
	char payment [20];   //payment type
	int delivery;   //delivery cost
	char courier [20];   //name of courier
} order;   //new struct type for each order in file

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);  //synchronizing input and output in correct way

	FILE *file;
	file = fopen("flowerSalesDB_October2011.txt", "r"); //opening file with data to read

	if (file == NULL) {
		printf("Problem opening file.");
		return 1;
	}   // if there is a problem with opening file, program will print it

	int i=-1;   //declaration with initialization of i to use it further as the number of orders overall
	order ord[200];   //array of structs to store data from the file
	while (!feof(file)) {   //while loop for reading in the data till the end of the file
		i++;    //incrementing i to store each order in different structs
		fscanf(file, "%i", &ord[i].id);   //starts from i=0, since we already incremented it
		fscanf(file, "%i", &ord[i].day);
		fscanf(file, "%i", &ord[i].quantity);   // similarly for all
		fscanf(file, "%s", ord[i].type);   //storing each data to corresponding elements of struct
		fscanf(file, "%lf", &ord[i].cost);
		fscanf(file, "%s", ord[i].arrangement);
		fscanf(file, "%s", ord[i].payment);
		fscanf(file, "%i", &ord[i].delivery);
		fscanf(file, "%s", ord[i].courier);
	}//so on it stores each order in each struct starting from i=0 and till the end of the file
//the last struct read by program would be ord[i], but it will contain garbage
//because it will firstly read empty row and then loop ends
//therefore we need only orders from ord[0] to ord[i-1], everything further is garbage
    fclose(file);//closing the file

    int j;   //declaring the integer to read the number given by user
	printf("Input the day in the form of an integer (1-31):");
	scanf("%i", &j);

	while (0<j && j<32) {   //loop to repeat the program till user inputs the number outside the range
        int k;    //number which will be used in loop further
        int orders=0;   //the total number of orders
        int flowers=0;   //the total number of flowers
        int bouquets=0;   //the total number of bouquets
        int gifts=0;   //the total number of gifts
        double cost=0;   //the total cost of orders
        double cash=0, paypal=0, halyq=0, Epay=0, yandex=0, qiwi=0, web=0;
//the total cost of orders for each payment type
        int delivery_number=0, delivery_cost=0;
//the total number and cost of deliveries
        int azat=0, qanat=0, shapaghat=0;
//the number of deliveries for each courier
        for (k=0; k<i; k++) { //loop for checking the each order struct from 0 to i-1
        	if(ord[k].day == j) { //taking only orders of day j
        		orders++;//increasing the number of orders for the day j

        		switch (ord[k].type[0]) {   //switch statement for first letter of type
        		   case 'g' :   //if first letter is g(corresponds to gift)
        			   gifts++;   //increments the number of gifts for day j
        			   break;
        		   default :   //if another letter
        			   flowers = flowers + ord[k].quantity; //increments the number of flowers
        			   if(ord[k].type[1] != 'o') {//if second letter is not o(corresponds to another from box)
        			       bouquets++; //increments the number of bouquets
        			   }
        			   break;
        		}

        		cost = cost + ord[k].cost;//increasing the total cost of the orders

        		switch (ord[k].payment[0]) { //switch statement for the first letter of payment type
        		   case 'c' :    //if c(corresponds to cash)
        			   cash = cash + ord[k].cost; //increments the total cost payed by cash
        			   break; //similarly for others
        		   case 'h'	: //halyq_bank
        			   halyq = halyq + ord[k].cost;
        			   break;
        		   case 'y' : //yandex_money
        			   yandex = yandex + ord[k].cost;
        			   break;
        		   case 'E'	: //epay_kazkom
        			   Epay = Epay + ord[k].cost;
        			   break;
        		   case 'p' : //paypal
        			   paypal = paypal + ord[k].cost;
        			   break;
        		   case 'w'	: //web_money
        			   web = web + ord[k].cost;
        			   break;
        		   default : //default is for qiwi or Qiwi
        			   qiwi = qiwi + ord[k].cost;
        			   break;
        		}

        		if(ord[k].delivery != 0) { //if delivery cost is not 0
        			delivery_number++; //increments the number of deliveries
        			delivery_cost = delivery_cost + ord[k].delivery; //increments the cost of deliveries
        		}

        		switch (ord[k].courier[0]) { //switch statement for the first letter of the courier's name
        		   case 'a' : //if first letter is a(corresponds to Azat)
        			   azat++; //increments the number of Azat's deliveries
        			   break; // similarly for others
        		   case 'q' : //Qanat_agha
        			   qanat++;
        			   break;
        		   case 's' : //Shapaghat
        			   shapaghat++;
        			   break;
        		}

        	}
        }
        //max is a most number of deliveries made among couriers
        int max = (azat>qanat) ? azat : qanat; //if (azat>qanat) => max=azat, else max=qanat
        max = (shapaghat>max) ? shapaghat : max;//if (shapaghat>max) => max=shapaghat, else max remains
//printing all the needed values
        printf("\nThe analysis for the day %i of the October:\n", j);
        printf("\na. The number of orders: %i\n", orders);
        printf("\nb. The number of flowers: %i\n", flowers);
        printf("\nc. The number of bouquets: %i\n", bouquets);
        printf("\nd. The number of gifts: %i\n", gifts);
        if (gifts != 0) { //if number of gifts equal to 0, it will print nothing
        	printf("List of gifts:\n"); //else it will print it
        }

        for (k=0; k<i; k++) {  //then if there are some gifts
        	if(ord[k].day == j) {//for the corresponding day
        		if(ord[k].type[0] == 'g') {//for the order with type beginning with g(gift)
        			printf("%s\n", ord[k].arrangement);//it will print arrangement of each order
        		}
        	}
        }

        printf("\ne. The total cost of the order: %.2f\n", cost);
        printf("\nf. The total costs broken down by payment type:\n");
        printf("i. Cash: %.2f\n", cash);
        printf("ii. Halyq_Bank: %.2f\n", halyq);
        printf("iii. Yandex_Money: %.2f\n", yandex);
        printf("iv. Epay_Kazkom: %.2f\n", Epay);
        printf("v. PayPal: %.2f\n", paypal);
        printf("vi. Web_Money: %.2f\n", web);
        printf("vii. Qiwi: %.2f\n", qiwi);
        printf("\ng. The number of deliveries: %i\n", delivery_number);
        printf("The total amount of money spent on deliveries: %i\n", delivery_cost);

        if (delivery_number>0) {//if the delivery number is bigger than 0
        printf("\nh. Courier/couriers made the most deliveries:\n");
//it will print part h
        if (max == azat) {//if the number most deliveries is equal to Azat's number of deliveries
        	printf("Azat\n");//it will print Azat's name
        }//similarly for others
        if (max == qanat) {
        	printf("Qanat_agha\n");
        }
        if (max == shapaghat) {
            printf("Shapaghat\n");
        }
//printing max number of deliveries
        printf("The number of deliveries made by him/each of them: %i\n", max);
        } else {//if there were no deliveries it will print following
        	printf("\nh. This day no deliveries were made by couriers.\n");
        }

        printf("\n\nInput the day in the form of an integer (1-31):");
		scanf("%i", &j);//asks for new day
	}

	printf("\nEnd of the program.");//ends the program if number is out of range

	return 0;
}
