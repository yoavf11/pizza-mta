#include <stdio.h>
#pragma warning(disable:4996)


#define DEFAULT_LENGTH 40
#define DEFAULT_WIDTH 50
#define TAX 1.17
#define BASIC_PRICE 70

#define OLIVES_PRICE 10
#define MUSHROOMS_PRICE 12
#define TOMATOES_PRICE 9
#define PINEAPPLE_PRICE 14
#define NO_TOPPINGS_PRICE 0

#define REGULAR_DOUGH_PRICE 0
#define VEGAN_DOUGH_PRICE 5
#define WHOLE_DOUGH_PRICE 3
#define GLUTEN_DOUGH_PRICE 4

#define REGULAR_DOUGH_TYPE 'r'
#define VEGAN_DOUGH_TYPE 'v'
#define WHOLE_DOUGH_TYPE 'w'
#define GLUTEN_DOUGH_TYPE 'f'

#define OLIVES_CHAR 'O'
#define MUSHROOMS_CHAR 'M'
#define TOMATOES_CHAR 'T'
#define PINEAPPLE_CHAR 'P'
#define NONE_CHAR ' '
#define HALF 2
#define CRUST 2



#define NO_TOPPINGS 0
#define FULL_TOPPINGS 1
#define HALF_TOPPINGS 2
#define QUARTER_TOPPINGS 3

#define FULL_PIZZA 1
#define HALF_PIZZA 0.5
#define QUARTER_PIZZA 0.25

#define NO_DELIVERY 0
#define DELIVERY 1
#define DELIVERY_PRICE 15

#define MIN_SIZE 10
#define MAX_WIDTH 80
#define MAX_LENGTH 40

#define MAX_ID_LENGTH 999999999

typedef struct Pizza {
	int length; // pizza length (cm)
	int width; // pizza width (cm)
	char doughType; // dough type ('r'/'v'/'w'/'f')
	int olives; // olives amount (0/1/0.5/0.25)
	int mushrooms; // mushrooms amount (0/1/0.5/0.25)
	int tomatoes; // tomatoes amount (0/1/0.5/0.25)
	int pineapple; // pineapple amount (0/1/0.5/0.25)
	double olivesPrice, mushroomsPrice, tomatoesPrice, pineapplePrice, doughPrice; // toppings price calc
	double olivesAmount, mushroomsAmount, tomatoesAmount, pineappleAmount;
	char q1; // topping type on first quarter ('O'/'M'/'T'/'P')
	char q2; // topping type on second quarter ('O'/'M'/'T'/'P')
	char q3; // topping type on third quarter ('O'/'M'/'T'/'P')
	char q4; // topping type on fourth quarter ('O'/'M'/'T'/'P')
	double price; // pizza price (without tax)
	int i; // pizzas amount counter
}PIZZA;

void welcomeMessage() { //print welcome message
	printf(" Welcome to MTA-Pizza!\n\n");
	printf("*****\n ***\n  *\n\n");
}
int getIDNumber(int* idNum) { // get user ID number
	int sum = 0, checkDigit, copyOfIDNum, tempDig;
	printf("\nPlease enter your ID number: ");
	scanf("%d", &*idNum);



	if (*idNum > MAX_ID_LENGTH || *idNum==0) {
		while (*idNum > MAX_ID_LENGTH || *idNum==0) {

			printf("\nInvalid ID number! Try again.");
			printf("\nPlease enter your ID number: ");
			scanf("%d", &*idNum);


		}
	}

	checkDigit = *idNum % 10;
	copyOfIDNum = (*idNum - checkDigit) / 10;


	while (copyOfIDNum > 0) {
		tempDig = (copyOfIDNum % 10);
		copyOfIDNum = ((copyOfIDNum - tempDig) / 10);
		tempDig = (tempDig * 2);
		if (tempDig >= 10)
			tempDig = ((tempDig % 10) + (tempDig / 10));
		sum = sum + tempDig;

		tempDig = (copyOfIDNum % 10);
		sum = sum + tempDig;
		copyOfIDNum = ((copyOfIDNum - tempDig) / 10);
	}
	sum = sum + checkDigit;


	if ((sum % 10) > 0) {
		while ((sum % 10) > 0) {


			printf("\nInvalid check digit! Try again.\n");
			printf("Please enter your ID number: ");
			scanf("%d", &*idNum);


			if (*idNum > MAX_ID_LENGTH || *idNum == 0) {
				while (*idNum > MAX_ID_LENGTH || *idNum == 0) {

					printf("\nInvalid ID number! Try again.");
					printf("\nPlease enter your ID number: ");
					scanf("%d", &*idNum);
				}
			}

			checkDigit = *idNum % 10;
			copyOfIDNum = (*idNum - checkDigit) / 10;
			sum = 0;

			while (copyOfIDNum > 0) {
				tempDig = (copyOfIDNum % 10);
				copyOfIDNum = ((copyOfIDNum - tempDig) / 10);
				tempDig = (tempDig * 2);
				if (tempDig >= 10)
					tempDig = ((tempDig % 10) + (tempDig / 10));
				sum = sum + tempDig;

				tempDig = (copyOfIDNum % 10);
				sum = sum + tempDig;
				copyOfIDNum = ((copyOfIDNum - tempDig) / 10);
			}
			sum = sum + checkDigit;
		}
	}
		
	

	return *idNum;
}

void printMenu() { // print pizerria's menu
	printf("\n\nOur menu:\n*********\n");
	printf("Basic pizza: %.2f NIS for %dx%d size pizza\n", (float)BASIC_PRICE, DEFAULT_LENGTH, DEFAULT_WIDTH);

	printf("\nToppings for basic size pizza:");
	printf("\nOlives: %d NIS", OLIVES_PRICE);
	printf("\nMushrooms: %d NIS", MUSHROOMS_PRICE);
	printf("\nTomatoes: %d NIS", TOMATOES_PRICE);
	printf("\nPineapple: %d NIS\n", PINEAPPLE_PRICE);


	printf("\nDough type for basic size pizza:");
	printf("\nRegular: %d NIS", REGULAR_DOUGH_PRICE);
	printf("\nVegan: %d NIS", VEGAN_DOUGH_PRICE);
	printf("\nWhole wheat: %d NIS", WHOLE_DOUGH_PRICE);
	printf("\nGluten free: %d NIS\n", GLUTEN_DOUGH_PRICE);
}

int getNumOfPizzas(int* pizzasAmount) { // get number of pizzas
	printf("\nHow many pizzas would you like to order? \n");
	scanf("%d", &*pizzasAmount);

	if (*pizzasAmount <= 0) {
		while (*pizzasAmount <= 0)
		{
			printf("Invalid choice! Try again.\n");
			printf("\nHow many pizzas would you like to order? \n");
			scanf("%d", &*pizzasAmount);
		}
	}
	return *pizzasAmount;
}

PIZZA getPizzaDimentions(PIZZA* pizza) { // get pizza's dimentions
	printf("\nPlease enter your pizza's length (cm): ");
	scanf("%d", &(*pizza).length);
	if (((*pizza).length < MIN_SIZE) || ((*pizza).length > MAX_LENGTH) || ((*pizza).length % 2 != 0)) {
		while (((*pizza).length < MIN_SIZE) || ((*pizza).length > MAX_LENGTH) || ((*pizza).length % 2 != 0)) {

			printf("Invalid length! Try again.\n");
			printf("Please enter your pizza's length (cm): ");
			scanf("%d", &(*pizza).length);
		}
	}
	printf("Please enter your pizza's width (cm): ");
	scanf("%d", &(*pizza).width);
	if (((*pizza).width < MIN_SIZE) || ((*pizza).width > MAX_WIDTH) || ((*pizza).width % 2 != 0)) {
		while (((*pizza).width < MIN_SIZE) || ((*pizza).width > MAX_WIDTH) || ((*pizza).width % 2 != 0)) {

			printf("Invalid width! Try again.\n");
			printf("Please enter your pizza's width (cm): ");
			scanf("%d", &(*pizza).width);
		}
	}
	return *pizza;
}

PIZZA getDoughType(PIZZA* pizza) { // get pizza's dough type

	printf("\nPlease enter the pizza's dough type: \n");
	printf("%c - for regular\n", REGULAR_DOUGH_TYPE);
	printf("%c - for vegan\n", VEGAN_DOUGH_TYPE);
	printf("%c - for whole wheat\n", WHOLE_DOUGH_TYPE);
	printf("%c - for gluten-free\n", GLUTEN_DOUGH_TYPE);
	scanf(" %c", &(*pizza).doughType);

	if ((*pizza).doughType != REGULAR_DOUGH_TYPE && (*pizza).doughType != VEGAN_DOUGH_TYPE && (*pizza).doughType != WHOLE_DOUGH_TYPE && (*pizza).doughType != GLUTEN_DOUGH_TYPE) {
		while ((*pizza).doughType != REGULAR_DOUGH_TYPE && (*pizza).doughType != VEGAN_DOUGH_TYPE && (*pizza).doughType != WHOLE_DOUGH_TYPE && (*pizza).doughType != GLUTEN_DOUGH_TYPE) {
			printf("Invalid choice! Try again.\n");
			printf("\nPlease enter the pizza's dough type: \n");
			printf("%c - for regular\n", REGULAR_DOUGH_TYPE);
			printf("%c - for vegan\n", VEGAN_DOUGH_TYPE);
			printf("%c - for whole wheat\n", WHOLE_DOUGH_TYPE);
			printf("%c - for gluten-free\n", GLUTEN_DOUGH_TYPE);
			scanf(" %c", &(*pizza).doughType);
		}

	}

	switch ((*pizza).doughType) {
	case REGULAR_DOUGH_TYPE:
		(*pizza).doughPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * BASIC_PRICE);
		break;
	case VEGAN_DOUGH_TYPE:
		(*pizza).doughPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (BASIC_PRICE + VEGAN_DOUGH_PRICE));
		break;
	case WHOLE_DOUGH_TYPE:
		(*pizza).doughPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (BASIC_PRICE + WHOLE_DOUGH_PRICE));
		break;
	case GLUTEN_DOUGH_TYPE:
		(*pizza).doughPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (BASIC_PRICE + GLUTEN_DOUGH_PRICE));
		break;

	}
}


PIZZA getToppings(PIZZA* pizza) { // get user's topping choices

	printf("\nPlease choose the toppings:\n");

	//reset toppings prices
	(*pizza).olivesPrice = NO_TOPPINGS;
	(*pizza).mushroomsPrice = NO_TOPPINGS;
	(*pizza).tomatoesPrice = NO_TOPPINGS;
	(*pizza).pineapplePrice = NO_TOPPINGS;

	//reset toppings counters
	(*pizza).olivesAmount = NO_TOPPINGS;
	(*pizza).mushroomsAmount = NO_TOPPINGS;
	(*pizza).tomatoesAmount = NO_TOPPINGS;
	(*pizza).pineappleAmount = NO_TOPPINGS;

	(*pizza).q1 = NONE_CHAR;
	(*pizza).q2 = NONE_CHAR;
	(*pizza).q3 = NONE_CHAR;
	(*pizza).q4 = NONE_CHAR;



	//*==========*OLIVES*==========*//

	printf("Olives (choose 0-3):\n");
	printf("%d. None\n", NO_TOPPINGS);
	printf("%d. Whole pizza\n", FULL_TOPPINGS);
	printf("%d. Half pizza\n", HALF_TOPPINGS);
	printf("%d. Quarter pizza\n", QUARTER_TOPPINGS);
	scanf("%d", &(*pizza).olives);

	if ((*pizza).olives != NO_TOPPINGS && (*pizza).olives != FULL_TOPPINGS && (*pizza).olives != HALF_TOPPINGS && (*pizza).olives != QUARTER_TOPPINGS) {
		while ((*pizza).olives != NO_TOPPINGS && (*pizza).olives != FULL_TOPPINGS && (*pizza).olives != HALF_TOPPINGS && (*pizza).olives != QUARTER_TOPPINGS) {

			printf("Invalid choice! Try again.\n");
			printf("\nOlives (choose 0-3):\n");
			printf("%d. None\n", NO_TOPPINGS);
			printf("%d. Whole pizza\n", FULL_TOPPINGS);
			printf("%d. Half pizza\n", HALF_TOPPINGS);
			printf("%d. Quarter pizza\n", QUARTER_TOPPINGS);
			scanf("%d", &(*pizza).olives);
		}
	}

	switch ((*pizza).olives) {
	case NO_TOPPINGS: (*pizza).olivesPrice = NO_TOPPINGS;
		(*pizza).olivesAmount = NO_TOPPINGS;

		break;

	case FULL_TOPPINGS:
		(*pizza).olivesAmount = FULL_PIZZA;
		(*pizza).olivesPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (OLIVES_PRICE * FULL_PIZZA));

		(*pizza).q1 = OLIVES_CHAR;
		(*pizza).q2 = OLIVES_CHAR;
		(*pizza).q3 = OLIVES_CHAR;
		(*pizza).q4 = OLIVES_CHAR;

		break;

	case HALF_TOPPINGS:
		(*pizza).olivesAmount = HALF_PIZZA;
		(*pizza).olivesPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (OLIVES_PRICE * HALF_PIZZA));

		(*pizza).q1 = OLIVES_CHAR;
		(*pizza).q2 = OLIVES_CHAR;


		break;

	case QUARTER_TOPPINGS:
		(*pizza).olivesAmount = QUARTER_PIZZA;
		(*pizza).olivesPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (OLIVES_PRICE * QUARTER_PIZZA));

		(*pizza).q1 = OLIVES_CHAR;



		break;

	}

	if ((*pizza).olivesAmount < FULL_PIZZA) {

		//*==========*MUSHROOMS*==========*//

		printf("Mushrooms (choose 0-3):\n");
		printf("%d. None\n", NO_TOPPINGS);
		printf("%d. Whole pizza\n", FULL_TOPPINGS);
		printf("%d. Half pizza\n", HALF_TOPPINGS);
		printf("%d. Quarter pizza\n", QUARTER_TOPPINGS);
		scanf("%d", &(*pizza).mushrooms);

		if ((*pizza).mushrooms != NO_TOPPINGS && (*pizza).mushrooms != FULL_TOPPINGS && (*pizza).mushrooms != HALF_TOPPINGS && (*pizza).mushrooms != QUARTER_TOPPINGS) {
			while ((*pizza).mushrooms != NO_TOPPINGS && (*pizza).mushrooms != FULL_TOPPINGS && (*pizza).mushrooms != HALF_TOPPINGS && (*pizza).mushrooms != QUARTER_TOPPINGS) {

				printf("Invalid choice! Try again.\n");
				printf("\nMushrooms (choose 0-3):\n");
				printf("%d. None\n", NO_TOPPINGS);
				printf("%d. Whole pizza\n", FULL_TOPPINGS);
				printf("%d. Half pizza\n", HALF_TOPPINGS);
				printf("%d. Quarter pizza\n", QUARTER_TOPPINGS);
				scanf("%d", &(*pizza).mushrooms);
			}
		}

		switch ((*pizza).mushrooms) {
		case NO_TOPPINGS: (*pizza).mushroomsPrice = NO_TOPPINGS;
			(*pizza).mushroomsAmount = NO_TOPPINGS;
			break;

		case FULL_TOPPINGS:
			(*pizza).mushroomsAmount = FULL_PIZZA;
			(*pizza).mushroomsPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (MUSHROOMS_PRICE * FULL_PIZZA));


			break;

		case HALF_TOPPINGS:
			(*pizza).mushroomsAmount = HALF_PIZZA;
			(*pizza).mushroomsPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (MUSHROOMS_PRICE * HALF_PIZZA));



			break;

		case QUARTER_TOPPINGS:
			(*pizza).mushroomsAmount = QUARTER_PIZZA;
			(*pizza).mushroomsPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (MUSHROOMS_PRICE * QUARTER_PIZZA));


			break;


		}

		if ((*pizza).olivesAmount + (*pizza).mushroomsAmount > FULL_TOPPINGS) {
			while ((*pizza).olivesAmount + (*pizza).mushroomsAmount > FULL_TOPPINGS) {

				(*pizza).mushroomsAmount = NO_TOPPINGS;
				(*pizza).mushroomsPrice = 0;

				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.\n");
				printf("%d. None\n", NO_TOPPINGS);
				printf("%d. Whole pizza\n", FULL_TOPPINGS);
				printf("%d. Half pizza\n", HALF_TOPPINGS);
				printf("%d. Quarter pizza\n", QUARTER_TOPPINGS);
				scanf("%d", &(*pizza).mushrooms);

				if ((*pizza).mushrooms != NO_TOPPINGS && (*pizza).mushrooms != FULL_TOPPINGS && (*pizza).mushrooms != HALF_TOPPINGS && (*pizza).mushrooms != QUARTER_TOPPINGS) {
					while ((*pizza).mushrooms != NO_TOPPINGS && (*pizza).mushrooms != FULL_TOPPINGS && (*pizza).mushrooms != HALF_TOPPINGS && (*pizza).mushrooms != QUARTER_TOPPINGS) {

						printf("Invalid choice! Try again.\n");
						printf("\nMushrooms (choose 0-3):\n");
						printf("%d. None\n", NO_TOPPINGS);
						printf("%d. Whole pizza\n", FULL_TOPPINGS);
						printf("%d. Half pizza\n", HALF_TOPPINGS);
						printf("%d. Quarter pizza\n", QUARTER_TOPPINGS);
						scanf("%d", &(*pizza).mushrooms);
					}
				}

				switch ((*pizza).mushrooms) {
				case NO_TOPPINGS: (*pizza).mushroomsPrice = NO_TOPPINGS;
					(*pizza).mushroomsAmount = NO_TOPPINGS;
					break;

				case FULL_TOPPINGS:
					(*pizza).mushroomsAmount = FULL_PIZZA;
					(*pizza).mushroomsPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (MUSHROOMS_PRICE * FULL_PIZZA));


				case HALF_TOPPINGS:
					(*pizza).mushroomsAmount = HALF_PIZZA;
					(*pizza).mushroomsPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (MUSHROOMS_PRICE * HALF_PIZZA));

					break;

				case QUARTER_TOPPINGS:
					(*pizza).mushroomsAmount = QUARTER_PIZZA;
					(*pizza).mushroomsPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (MUSHROOMS_PRICE * QUARTER_PIZZA));

					break;

				}

			}
		}

		switch ((*pizza).mushrooms) {

		case FULL_TOPPINGS:

			//*calc quarters*//
			(*pizza).q1 = MUSHROOMS_CHAR;
			(*pizza).q2 = MUSHROOMS_CHAR;
			(*pizza).q3 = MUSHROOMS_CHAR;
			(*pizza).q4 = MUSHROOMS_CHAR;

			break;

		case HALF_TOPPINGS:
			//*calc quarters*//
			if ((*pizza).q1 == NONE_CHAR && (*pizza).q2 == NONE_CHAR) {
				(*pizza).q1 = MUSHROOMS_CHAR;
				(*pizza).q2 = MUSHROOMS_CHAR;



			}

			else if ((*pizza).q1 != NONE_CHAR && (*pizza).q2 != NONE_CHAR) {
				(*pizza).q3 = MUSHROOMS_CHAR;
				(*pizza).q4 = MUSHROOMS_CHAR;


			}

			else if ((*pizza).q1 != NONE_CHAR && (*pizza).q2 == NONE_CHAR) {
				(*pizza).q2 = MUSHROOMS_CHAR;
				(*pizza).q3 = MUSHROOMS_CHAR;

			}

			break;

		case QUARTER_TOPPINGS:
			//*calc quarters*//
			if ((*pizza).q1 == NONE_CHAR) {
				(*pizza).q1 = MUSHROOMS_CHAR;



			}

			else if ((*pizza).q1 != NONE_CHAR && (*pizza).q2 == NONE_CHAR) {
				(*pizza).q2 = MUSHROOMS_CHAR;


			}

			else if ((*pizza).q1 != NONE_CHAR && (*pizza).q2 != NONE_CHAR) {
				(*pizza).q3 = MUSHROOMS_CHAR;


			}

			break;

		}
	}


	//*============================*//

	if ((*pizza).olivesAmount + (*pizza).mushroomsAmount < FULL_PIZZA) {

		//*==========*TOMATOES*==========*//

		printf("Tomatos (choose 0-3):\n");
		printf("%d. None\n", NO_TOPPINGS);
		printf("%d. Whole pizza\n", FULL_TOPPINGS);
		printf("%d. Half pizza\n", HALF_TOPPINGS);
		printf("%d. Quarter pizza\n", QUARTER_TOPPINGS);
		scanf("%d", &(*pizza).tomatoes);

		if ((*pizza).tomatoes != NO_TOPPINGS && (*pizza).tomatoes != FULL_TOPPINGS && (*pizza).tomatoes != HALF_TOPPINGS && (*pizza).tomatoes != QUARTER_TOPPINGS) {
			while ((*pizza).tomatoes != NO_TOPPINGS && (*pizza).tomatoes != FULL_TOPPINGS && (*pizza).tomatoes != HALF_TOPPINGS && (*pizza).tomatoes != QUARTER_TOPPINGS) {

				printf("Invalid choice! Try again.\n");
				printf("Tomatos (choose 0-3):\n");
				printf("%d. None\n", NO_TOPPINGS);
				printf("%d. Whole pizza\n", FULL_TOPPINGS);
				printf("%d. Half pizza\n", HALF_TOPPINGS);
				printf("%d. Quarter pizza\n", QUARTER_TOPPINGS);
				scanf("%d", &(*pizza).tomatoes);
			}
		}

		switch ((*pizza).tomatoes) {
		case NO_TOPPINGS: (*pizza).tomatoesPrice = NO_TOPPINGS;
			(*pizza).tomatoesAmount = NO_TOPPINGS;
			break;

		case FULL_TOPPINGS:
			(*pizza).tomatoesAmount = FULL_PIZZA;
			(*pizza).tomatoesPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (TOMATOES_PRICE * FULL_PIZZA));


			break;

		case HALF_TOPPINGS:
			(*pizza).tomatoesAmount = HALF_PIZZA;
			(*pizza).tomatoesPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (TOMATOES_PRICE * HALF_PIZZA));



			break;

		case QUARTER_TOPPINGS:
			(*pizza).tomatoesAmount = QUARTER_PIZZA;
			(*pizza).tomatoesPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (TOMATOES_PRICE * QUARTER_PIZZA));


			break;


		}


		if ((*pizza).olivesAmount + (*pizza).mushroomsAmount + (*pizza).tomatoesAmount> FULL_TOPPINGS) {
			while ((*pizza).olivesAmount + (*pizza).mushroomsAmount+(*pizza).tomatoesAmount > FULL_TOPPINGS) {

				(*pizza).tomatoesAmount = NO_TOPPINGS;
				(*pizza).tomatoesPrice = 0;

			
				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.\n");
				printf("%d. None\n", NO_TOPPINGS);
				printf("%d. Whole pizza\n", FULL_TOPPINGS);
				printf("%d. Half pizza\n", HALF_TOPPINGS);
				printf("%d. Quarter pizza\n", QUARTER_TOPPINGS);
				scanf("%d", &(*pizza).tomatoes);

				if ((*pizza).tomatoes != NO_TOPPINGS && (*pizza).tomatoes != FULL_TOPPINGS && (*pizza).tomatoes != HALF_TOPPINGS && (*pizza).tomatoes != QUARTER_TOPPINGS) {
					while ((*pizza).tomatoes != NO_TOPPINGS && (*pizza).tomatoes != FULL_TOPPINGS && (*pizza).tomatoes != HALF_TOPPINGS && (*pizza).tomatoes != QUARTER_TOPPINGS) {

						printf("Invalid choice! Try again.\n");
						printf("Tomatos (choose 0-3):\n");
						printf("%d. None\n", NO_TOPPINGS);
						printf("%d. Whole pizza\n", FULL_TOPPINGS);
						printf("%d. Half pizza\n", HALF_TOPPINGS);
						printf("%d. Quarter pizza\n", QUARTER_TOPPINGS);
						scanf("%d", &(*pizza).tomatoes);
					}
				}

				switch ((*pizza).tomatoes) {
				case NO_TOPPINGS: (*pizza).tomatoesPrice = NO_TOPPINGS;
					(*pizza).tomatoesAmount = NO_TOPPINGS;
					break;

				case FULL_TOPPINGS:
					(*pizza).tomatoesAmount = FULL_PIZZA;
					(*pizza).tomatoesPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (TOMATOES_PRICE * FULL_PIZZA));


					break;

				case HALF_TOPPINGS:
					(*pizza).tomatoesAmount = HALF_PIZZA;
					(*pizza).tomatoesPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (TOMATOES_PRICE * HALF_PIZZA));


					break;

				case QUARTER_TOPPINGS:
					(*pizza).tomatoesAmount = QUARTER_PIZZA;
					(*pizza).tomatoesPrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (TOMATOES_PRICE * QUARTER_PIZZA));


					break;


				}
			}
		}


		switch ((*pizza).tomatoes) {

		case FULL_TOPPINGS:

			//*calc quarters*//
			(*pizza).q1 = TOMATOES_CHAR;
			(*pizza).q2 = TOMATOES_CHAR;
			(*pizza).q3 = TOMATOES_CHAR;
			(*pizza).q4 = TOMATOES_CHAR;

			break;

		case HALF_TOPPINGS:

			//*calc quarters*//
			if ((*pizza).q1 == NONE_CHAR && (*pizza).q2 == NONE_CHAR) {
				(*pizza).q1 = TOMATOES_CHAR;
				(*pizza).q2 = TOMATOES_CHAR;


			}

			else if ((*pizza).q1 != NONE_CHAR && (*pizza).q2 != NONE_CHAR) {
				(*pizza).q3 = TOMATOES_CHAR;
				(*pizza).q4 = TOMATOES_CHAR;
			}

			else if ((*pizza).q1 != NONE_CHAR && (*pizza).q2 == NONE_CHAR) {
				(*pizza).q2 = TOMATOES_CHAR;
				(*pizza).q3 = TOMATOES_CHAR;

			}

			break;

		case QUARTER_TOPPINGS:

			//*calc quarters*//
			if ((*pizza).q1 == NONE_CHAR) {
				(*pizza).q1 = TOMATOES_CHAR;

			}

			else if ((*pizza).q1 != NONE_CHAR && (*pizza).q2 == NONE_CHAR) {
				(*pizza).q2 = TOMATOES_CHAR;

			}

			else if ((*pizza).q1 != NONE_CHAR && (*pizza).q2 != NONE_CHAR && (*pizza).q3 == NONE_CHAR) {
				(*pizza).q3 = TOMATOES_CHAR;
			}


			else if ((*pizza).q1 != NONE_CHAR && (*pizza).q2 != NONE_CHAR && (*pizza).q3 != NONE_CHAR) {
				(*pizza).q4 = TOMATOES_CHAR;
			}

			break;
		}


	}


	//*============================*//

	if (((*pizza).olivesAmount + (*pizza).mushroomsAmount + (*pizza).tomatoesAmount) < FULL_PIZZA) {

		//*==========*PINEAPPLE*==========*//

		printf("Pineapple (choose 0-3):\n");
		printf("%d. None\n", NO_TOPPINGS);
		printf("%d. Whole pizza\n", FULL_TOPPINGS);
		printf("%d. Half pizza\n", HALF_TOPPINGS);
		printf("%d. Quarter pizza\n", QUARTER_TOPPINGS);
		scanf("%d", &(*pizza).pineapple);

		if ((*pizza).pineapple != NO_TOPPINGS && (*pizza).pineapple != FULL_TOPPINGS && (*pizza).pineapple != HALF_TOPPINGS && (*pizza).pineapple != QUARTER_TOPPINGS) {
			while ((*pizza).pineapple != NO_TOPPINGS && (*pizza).pineapple != FULL_TOPPINGS && (*pizza).pineapple != HALF_TOPPINGS && (*pizza).pineapple != QUARTER_TOPPINGS) {

				printf("Invalid choice! Try again.\n");
				printf("\nPineapple (choose 0-3):\n");
				printf("%d. None\n", NO_TOPPINGS);
				printf("%d. Whole pizza\n", FULL_TOPPINGS);
				printf("%d. Half pizza\n", HALF_TOPPINGS);
				printf("%d. Quarter pizza\n", QUARTER_TOPPINGS);
				scanf("%d", &(*pizza).pineapple);
			}
		}

		switch ((*pizza).pineapple) {
		case NO_TOPPINGS: (*pizza).pineapplePrice = NO_TOPPINGS;
			(*pizza).pineappleAmount = NO_TOPPINGS;
			break;

		case FULL_TOPPINGS:
			(*pizza).pineappleAmount = FULL_PIZZA;
			(*pizza).pineapplePrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (PINEAPPLE_PRICE * FULL_PIZZA));

			break;

		case HALF_TOPPINGS:
			(*pizza).pineappleAmount = HALF_PIZZA;
			(*pizza).pineapplePrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (PINEAPPLE_PRICE * HALF_PIZZA));

			break;

		case QUARTER_TOPPINGS:
			(*pizza).pineappleAmount = QUARTER_PIZZA;
			(*pizza).pineapplePrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (PINEAPPLE_PRICE * QUARTER_PIZZA));

			break;
		}

		if (((*pizza).olivesAmount + (*pizza).mushroomsAmount + (*pizza).tomatoesAmount + (*pizza).pineappleAmount) > FULL_TOPPINGS) {
			while (((*pizza).olivesAmount + (*pizza).pineappleAmount + (*pizza).pineappleAmount + (*pizza).pineappleAmount) > FULL_TOPPINGS) {
				(*pizza).pineappleAmount = NO_TOPPINGS;
				(*pizza).pineapplePrice = 0;

				printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.\n");
				printf("%d. None\n", NO_TOPPINGS);
				printf("%d. Whole pizza\n", FULL_TOPPINGS);
				printf("%d. Half pizza\n", HALF_TOPPINGS);
				printf("%d. Quarter pizza\n", QUARTER_TOPPINGS);
				scanf("%d", &(*pizza).pineapple);

				if ((*pizza).pineapple != NO_TOPPINGS && (*pizza).pineapple != FULL_TOPPINGS && (*pizza).pineapple != HALF_TOPPINGS && (*pizza).pineapple != QUARTER_TOPPINGS) {
					while ((*pizza).pineapple != NO_TOPPINGS && (*pizza).pineapple != FULL_TOPPINGS && (*pizza).pineapple != HALF_TOPPINGS && (*pizza).pineapple != QUARTER_TOPPINGS) {

						printf("Invalid choice! Try again.\n");
						printf("\nPineapple (choose 0-3):\n");
						printf("%d. None\n", NO_TOPPINGS);
						printf("%d. Whole pizza\n", FULL_TOPPINGS);
						printf("%d. Half pizza\n", HALF_TOPPINGS);
						printf("%d. Quarter pizza\n", QUARTER_TOPPINGS);
						scanf("%d", &(*pizza).pineapple);
					}
				}

				switch ((*pizza).pineapple) {
				case NO_TOPPINGS: (*pizza).pineapplePrice = NO_TOPPINGS;
					(*pizza).pineappleAmount = NO_TOPPINGS;
					break;

				case FULL_TOPPINGS:
					(*pizza).pineappleAmount = FULL_PIZZA;
					(*pizza).pineapplePrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (PINEAPPLE_PRICE * FULL_PIZZA));

					break;

				case HALF_TOPPINGS:
					(*pizza).pineappleAmount = HALF_PIZZA;
					(*pizza).pineapplePrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (PINEAPPLE_PRICE * HALF_PIZZA));


					break;

				case QUARTER_TOPPINGS:
					(*pizza).pineappleAmount = QUARTER_PIZZA;
					(*pizza).pineapplePrice = ((((double)(*pizza).width * (double)(*pizza).length) / (DEFAULT_LENGTH * DEFAULT_WIDTH)) * (PINEAPPLE_PRICE * QUARTER_PIZZA));

					break;

				}

			}
		}


		switch ((*pizza).pineapple) {

		case FULL_TOPPINGS:

			//*calc quarters*//
			(*pizza).q1 = PINEAPPLE_CHAR;
			(*pizza).q2 = PINEAPPLE_CHAR;
			(*pizza).q3 = PINEAPPLE_CHAR;
			(*pizza).q4 = PINEAPPLE_CHAR;

			break;

		case HALF_TOPPINGS:

			//*calc quarters*//
			if ((*pizza).q1 == NONE_CHAR && (*pizza).q2 == NONE_CHAR) {
				(*pizza).q1 = PINEAPPLE_CHAR;
				(*pizza).q2 = PINEAPPLE_CHAR;

			}

			else if ((*pizza).q1 != NONE_CHAR && (*pizza).q2 != NONE_CHAR) {
				(*pizza).q3 = PINEAPPLE_CHAR;
				(*pizza).q4 = PINEAPPLE_CHAR;
			}

			else if ((*pizza).q1 != NONE_CHAR && (*pizza).q2 == NONE_CHAR) {
				(*pizza).q2 = PINEAPPLE_CHAR;
				(*pizza).q3 = PINEAPPLE_CHAR;
			}

			break;

		case QUARTER_TOPPINGS:

			//*calc quarters*//
			if ((*pizza).q1 == NONE_CHAR) {
				(*pizza).q1 = PINEAPPLE_CHAR;

			}

			else if ((*pizza).q1 != NONE_CHAR && (*pizza).q2 == NONE_CHAR) {
				(*pizza).q2 = PINEAPPLE_CHAR;

			}

			else if ((*pizza).q1 != NONE_CHAR && (*pizza).q2 != NONE_CHAR && (*pizza).q3 == NONE_CHAR) {
				(*pizza).q3 = PINEAPPLE_CHAR;
			}


			else if ((*pizza).q1 != NONE_CHAR && (*pizza).q2 != NONE_CHAR && (*pizza).q3 != NONE_CHAR) {
				(*pizza).q4 = PINEAPPLE_CHAR;
			}

			break;
		}

	}


	//*============================*//

	return *pizza;
}



void printPizza(PIZZA* pizza) { // print pizza's painting
	for (int i = 0; i < (*pizza).width; i++) {
		printf("%c", (*pizza).doughType);
	}
	printf("\n");

	for (int k = 0; k < (((*pizza).length) - CRUST) / HALF; k++) {
		printf("%c", (*pizza).doughType);
		for (int i = 0; i < ((*pizza).width - CRUST) / HALF; i++) {
			printf("%c", (*pizza).q4);
		}
		for (int i = 0; i < ((*pizza).width - CRUST) / HALF; i++) {
			printf("%c", (*pizza).q1);
		}
		printf("%c", (*pizza).doughType);
		printf("\n");
	}

	for (int k = 0; k < (((*pizza).length) - CRUST) / HALF; k++) {
		printf("%c", (*pizza).doughType);
		for (int i = 0; i < ((*pizza).width - CRUST) / HALF; i++) {
			printf("%c", (*pizza).q3);
		}
		for (int i = 0; i < ((*pizza).width - CRUST) / HALF; i++) {
			printf("%c", (*pizza).q2);
		}
		printf("%c", (*pizza).doughType);
		printf("\n");
	}

	for (int i = 0; i < (*pizza).width; i++) {
		printf("%c", (*pizza).doughType);
	}
	printf("\n\n");
}

void printPizzaDetails(PIZZA* pizza, int* pizzasAmount, double* totalPrice) { // print pizza details summary

	for ((*pizza).i = 1; (*pizza).i <= *pizzasAmount; (*pizza).i++) {
		printf("*************************************************\n");
		printf("Pizza #%d:\n", (*pizza).i);

		getPizzaDimentions(&*pizza);
		getDoughType(&*pizza);
		getToppings(&*pizza);

		//pizza summary
		(*pizza).price = ((*pizza).doughPrice + (*pizza).olivesPrice + (*pizza).mushroomsPrice + (*pizza).tomatoesPrice + (*pizza).pineapplePrice);

		printf("\nPizza #%d details:\n", (*pizza).i);
		printf("*******************\n");
		printf("Pizza size: %dx%d\n", (*pizza).length, (*pizza).width);
		printf("Pizza price (without tax): %.2f\n\n", (*pizza).price);
		printPizza(&*pizza);

		*totalPrice = *totalPrice + (*pizza).price;
	}

}

int getDelivery(double* totalPrice, int* isDelivery) { // delivery addition
	printf("*************************************************\n");
	printf("Do you want delivery for the price of 15 NIS? Enter 1 for delivery or 0 for pick-up: ");
	scanf("%d", &*isDelivery);

	if (*isDelivery != DELIVERY && *isDelivery != NO_DELIVERY) {
		while (*isDelivery != DELIVERY && *isDelivery != NO_DELIVERY) {
			printf("Invalid choice! Try again.");
			printf("\nDo you want delivery for the price of 15 NIS? Enter 1 for delivery or 0 for pick-up: ");
			scanf("%d", &*isDelivery);
		}
	}

	switch (*isDelivery) {
	case 1: *isDelivery = DELIVERY_PRICE;
		*totalPrice = *totalPrice + *isDelivery;
		break;
	case 0: *isDelivery = NO_DELIVERY;
		break;
	}
	return *isDelivery, *totalPrice;
}

void getPayment(double* totalPrice, int* totalPriceWTax) { //patment calc	
	int payment, change, tempBalance;
	int numOfTens, numOfFives, numOfTwos, numOfOnes;


	//payment
	printf("\nPlease enter your payment: ");
	scanf("%d", &payment);

	//calc balance
	if (payment < *totalPriceWTax) {
		while (payment < *totalPriceWTax) {
			printf("Your remaining balance is: %d\n", *totalPriceWTax - payment);
			printf("Please enter your payment: ");
			scanf("%d", &tempBalance);
			payment = payment + tempBalance;
		}
	}
	//calc change
	if (payment > *totalPriceWTax) {
		change = payment - *totalPriceWTax;
		printf("Your change is %d NIS using:\n", change);

		numOfTens = change / 10;
		if (numOfTens > 0) {
			printf("%d coin(s) of ten\n", numOfTens);
			change = change - (numOfTens * 10);
		}
		numOfFives = change / 5;
		if (numOfFives > 0) {
			printf("%d coin(s) of five\n", numOfFives);
			change = change - (numOfFives * 5);
		}
		numOfTwos = change / 2;
		if (numOfTwos > 0) {
			printf("%d coin(s) of two\n", numOfTwos);
			change = change - (numOfTwos * 2);
		}
		numOfOnes = change / 1;
		if (numOfOnes > 0)
			printf("%d coin(s) of one\n", numOfOnes);
	}
	printf("Thank you for your order!");
}


void main() {


	int pizzasAmount;
	int idNum;
	double totalPrice = 0;
	int totalPriceWTax = 0;
	int isDelivery = 0;

	welcomeMessage();
	getIDNumber(&idNum);
	printMenu();
	getNumOfPizzas(&pizzasAmount);
	PIZZA pizza;
	printPizzaDetails(&pizza, &pizzasAmount, &totalPrice);
	getDelivery(&totalPrice, &isDelivery);

	//order summary
	printf("\n\nYour order details:\n");
	printf("*******************\n\n");
	printf("ID number: %09d\n", idNum);
	printf("Number of pizzas: %d\n", pizzasAmount);
	if (isDelivery == DELIVERY_PRICE)
		printf("Delivery\n");

	else
		printf("Pick-up\n");
	printf("Total price: %.2f\n", totalPrice);
	totalPriceWTax = totalPrice * TAX;
	printf("Total price with tax (rounded down): %d\n", totalPriceWTax);

	getPayment(&totalPrice, &totalPriceWTax);
}
