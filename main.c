#include <math.h>
#include <stdio.h>

long long getCardNumbers();
void cardType(long long x);
int checkCard(long long x);
int evenZeroes(int zeroes, long long x, int sum);
int oddZeroes(int zeroes, long long x, int sum);

int main(void)
{
    // Prompts user for a card number
    long long x = getCardNumbers();
    // Validates, determine and print card type
    cardType(x);
}

// Prompts user for a card number
long long getCardNumbers()
{
    long long x;
    // Keep prompting user until they input a non-negative integer value
    do
    {
        //x = get_long("Number: ");
        printf("Number: ");
        scanf("%Ld", &x);
    }
    while (x < 0);
    return x;
}

// Validates, determine and print card type
int checkCard(long long x)
{
    // Checks if card number is at least 13 digits long
    if (x >= 1000000000000)
    {
        int zeroes = 0; 
        int sum = 0;
        // Stores the number of digits in zeroes
        for (long long y = x; y > 0; y /= 10)
        {
            ++zeroes;
        }
        // Check if the number of digits is odd or even
        if (zeroes == 16)
        {
            sum = evenZeroes(zeroes, x, sum);   
        }
        else
        {
            sum = oddZeroes(zeroes, x, sum);
        }
        // Checks if the last digit of sum is 0
        if (sum % 10 == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

void cardType(long long x)
{
    // Calls the checkCard function to determine if the card number is valid
    if (checkCard(x))
    {
        // Stores the last two digits of the card number in x
        while (x > 100)
        {
            x /= 10;
        }
        // Discover the card type based on x
        if (x == 34 || x == 37)
        {
            printf("AMEX\n");
        }
        else if (x == 51 || x == 52 || x == 53 || x == 54 || x == 55)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            // This is because for VISA, the only prerequisite is that the first number is 4
            x /= 10;
            if (x == 4)
            {
                printf("VISA\n");
            }
            else
            {
                // INVALID  for numbers that don't start with none of the digits above
                printf("INVALID\n");
            }
        }
    }
    else
    {
        // INVALID for the card not following Luhn’s Algorithm
        printf("INVALID\n");
    }
}
// Calculates sum for numbers with an even number of digits
int evenZeroes(int zeroes, long long x, int sum)
{
    // The next line exists to make shure the whole number isn't transformed in 0 in the next sections
    --zeroes;
    while (zeroes > 0)
    {
        // Defining variables that temporarily store the value of x (card number)
        long long tempx0 = x;
        long long tempx1 = tempx0 / 10;
        // Loop that makes two numbers, one 10 * the other (hence the --zeroes line)
        for (int i = zeroes; i > 0; --i)
        {
            tempx0 /= 10;
            tempx1 /= 10;
        }
        // Creating a variable that in the future will hold the value of the double of a single digit 
        int digitBy2 = 0;
        // Checks if tempx1 is different from 0, so a division by 0 dosen't occour
        if (tempx1 != 0)
        {
            digitBy2 = (tempx0 % tempx1) * 2;
        }
        else
        {
            digitBy2 = tempx0 * 2;
        }
        // This section determines if the digit multiplyed by 2 is single digit or two digit
        // If the variable is storing a two digit number, the digits of that number will get summed
        if (digitBy2 <= 9)
        {
            sum += digitBy2;
        }
        else
        {
            sum += (digitBy2 % 10) + 1;
        }
        zeroes -= 2;
    }
    // Restoring zeroes to 0 for next step in Luhn’s Algorithm
    zeroes = 0;
    for (long long y = x; y > 0; y /= 10)
    {
        ++zeroes;
    }
    --zeroes;
    // This time the remaining digits will get summed
    while (zeroes >= 0)
    {
        long long tempx0 = x;
        long long tempx1 = tempx0 * 10;
        for (int i = zeroes; i > 0; --i)
        {
            tempx0 /= 10;
            tempx1 /= 10;
        }
        sum += tempx1 % (tempx0 * 10);
        zeroes -= 2;
    }
    // The total value of the sum is returned
    return sum;
}

// Calculates sum for numbers with an odd number of digits
int oddZeroes(int zeroes, long long x, int sum)
{
    // Variables that are used just as counting for loops or as parameters ajustments
    int count = 0;
    int foo = 0;
    int parameter;
    if (zeroes == 15)
    {
        parameter = 7;
    }
    else
    {
        parameter = 6;
    }
    // Loops 7 or 6 times because of number of digits
    while (count < parameter)
    { 
        long long tempx0 = x / 10;
        long long tempx1 = x;
        for (int i = zeroes - foo; i <= zeroes; ++i)
        {
            tempx0 /= 10;
            tempx1 /= 10;
        }
        // Variable created to hold the value of the digit * 2
        int digitBy2 = (tempx1 % (tempx0 * 10) * 2);
        // This section determines if the digit multiplyed by 2 is single digit or two digit
        // If the variable is storing a two digit number, the digits of that number will get summed
        if (digitBy2 <= 9)
        {
            sum += digitBy2;
        }
        else
        {
            sum += (digitBy2 % 10) + 1;
        }
        ++count;
        foo += 2;
    }
    // Reseting the value of these variable
    foo = 0;
    count = 0;
    zeroes = 0;
    for (long long y = x; y > 0; y /= 10)
    {
        ++zeroes;
    }
    // This time the remaining digits will get summed
    while (count <= 7)
    { 
        long long tempx0 = x / 10;
        long long tempx1 = x;
        for (int i = zeroes - foo; i < zeroes; ++i)
        {
            tempx0 /= 10;
            tempx1 /= 10;
        }
        // Line conditional necessary to avoid dividing by 0
        if (tempx0 != 0)
        {
            sum += tempx1 % (tempx0 * 10);
        }
        else
        {
            sum += tempx1;
        }
        ++count;
        foo += 2;
    }
    // The total value of the sum is returned
    return sum;
}
