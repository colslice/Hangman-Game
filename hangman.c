// hangman game using a random number generator to pick a word from a file.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void printHangman(int incorrect_count);
void printWord(char *player, char *answer, int num_letters);
int numLetters(char answer[30]);

int main(void)
{
    int incorrect_count = 0, N, num_letters, wrong;
    char answer[30], guess;
    int j, i = 0, k;

    // this block reads a random word and stores it in answer. We also find the number of letters in the word and initiaze "player" using that integer
    FILE *words = fopen("words.txt", "r");
    srand(time(NULL));
    N = rand() % 850; // 850 words in the words.txt file
    for (int i = 0; i < N; i++)
    {
        fscanf(words, "%s", answer);
    }
    num_letters = numLetters(answer);
    char player[num_letters], already_guessed[26];
    for (i = 0; i < num_letters; i++) // initialize the array
    {
        player[i] = '*';
    }

    for (i = 0; i < 26; i++) // initialize the array with null characters so we acn 
    {
        already_guessed[i] = '\0'; 
    }

    i = 0; // i keeps track of the current index of already_guessed

 
    while (incorrect_count != 8) // game control loop
    {
        int correct_letters = 0;
        wrong = 1; // "wrong" flag. 1 is true, 0 is false
        printHangman(incorrect_count);
        printWord(player, answer, num_letters);
        printf("\nAlready guessed: %s", already_guessed);
        printf("\nEnter a character: ");
        scanf(" %c", &guess); // Add a space before %c to consume any whitespace characters
        for (k = 0; k < i; k++) // keep prompting if the player keeps trying to guess the same letter
        {
            if (already_guessed[k] == guess)
            {
                printf("\nTry again. That letter has been guessed: ");
                scanf(" %c", &guess);
                k = -1; // k will be incremented by one by the for-loop, but we want it to be 0 again so we can check each letter in the already_guesses array
            }

        }

        for (j = 0; j < num_letters; j++)
        {
            if (guess == answer[j]) // 
            {
                player[j] = guess;
                wrong = 0; // set wrong to false
            }
        }
        for (k = 0; k < num_letters; k++) // current progress check to see if you guessed it 
        {
            if (player[k] == answer[k])
                correct_letters++;
        }
        if (correct_letters == num_letters) // everything is correct, so we can break the game control loop
            break;

        if (wrong == 1) // the "wrong" flag is true
        {
            incorrect_count++;
            already_guessed[i] = guess;
            i++;
        }
    }

    if (incorrect_count == 8) // player loses
    {
        printHangman(incorrect_count);
        printf("\nBetter luck next time! The word was %s\n", answer);
    }
    else // player wins
    {
        printf("\n%s", answer);
        printf("\nYou got it!\n");
    }

    fclose(words);

    return 0;
}

void printHangman(int incorrect_count) // prints the hangman based on the number of incorrect guesses
{
    switch (incorrect_count)
    {
    case 0:
        printf("\n\n\n\n\n\n");
        break;
    case 1:
        printf("\n\n\n\n\n\n");
        printf("   _______\n");
        break;
    case 2:
        printf("    +---+\n");
        printf("    |   |\n");
        printf("        |\n");
        printf("        |\n");
        printf("        |\n");
        printf("        |\n");
        printf("  =========\n");
        break;
    case 3:
        printf("    +---+\n");
        printf("    |   |\n");
        printf("    O   |\n");
        printf("        |\n");
        printf("        |\n");
        printf("        |\n");
        printf("  =========\n");
        break;
    case 4:
        printf("    +---+\n");
        printf("    |   |\n");
        printf("    O   |\n");
        printf("    |   |\n");
        printf("        |\n");
        printf("        |\n");
        printf("  =========\n");
        break;
    case 5:
        printf("    +---+\n");
        printf("    |   |\n");
        printf("    O   |\n");
        printf("   /|   |\n");
        printf("        |\n");
        printf("        |\n");
        printf("  =========\n");
        break;
    case 6:
        printf("    +---+\n");
        printf("    |   |\n");
        printf("    O   |\n");
        printf("   /|\\  |\n");
        printf("        |\n");
        printf("        |\n");
        printf("  =========\n");
        break;
    case 7:
        printf("    +---+\n");
        printf("    |   |\n");
        printf("    O   |\n");
        printf("   /|\\  |\n");
        printf("   /    |\n");
        printf("        |\n");
        printf("  =========\n");
        break;
    case 8:
        printf("    +---+\n");
        printf("    |   |\n");
        printf("    O   |\n");
        printf("   /|\\  |\n");
        printf("   / \\  |\n");
        printf("        |\n");
        printf("  =========\n");
        break;
    default:
        printf("Invalid number of guesses.\n");
        break;
    }
}

void printWord(char *player, char answer[30], int num_letters) // controls the printing of the blanks or correctly guessed letters
{

    for (int i = 0; i < num_letters; i++)
    {

        if (player[i] == '*')
        {
            printf("_ ");
        }

        else
            printf("%c ", answer[i]);
    }
}

int numLetters(char answer[30]) // counts the number of letters in the answer
{
    int i = 0;
    while (answer[i] != '\0')
    {
        i++;
    }
    return i;
}
