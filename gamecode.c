#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>

/*
| Guess the Number
| Created by Muhammad Ryan Fadholi
*/
void FinalReport(int *FalseCount, int *PlayCount, float *TotalScore);
bool ContinueQuestion(int FalseCount);
float ScoreCalc(int TurnCount,int PlayCount);
void FinalClue(int *Answer);

int main(void)
{
    int Answer,FalseCount,Guess,LastAnswer,PlayCount,TurnCount,i;
    float RoundScore[1001],TotalScore;
    bool answer_true,Continue,GuessTrue;
    srand(time(NULL));

    FalseCount = 0;TotalScore = 0;PlayCount = 0;LastAnswer = 0;
    printf("--------------------------------------------------------------------");
    printf("\n                            G U E S S ");
    printf("\n                              T H E  ");
    printf("\n                           N U M B E R");
    printf("\n--------------------------------------------------------------------");
    printf("\nThere is only one rule: Guess it right!");
    printf("\nThere will be a random number as the answer in the range of 1-10.");
    printf("\nYou just have to guess it right from 3 tries to win!");
    printf("\nYour game ends if you failed to guess 3 times OR you choose to end the game.");
    printf("\nGood Luck!");
    do
    {
        PlayCount++;
        Answer = rand() % 10 + 1;
        while (Answer == LastAnswer)
        {
            //This prevents same numbers getting chosen twice
            Answer = rand() % 10 + 1;
        }
        LastAnswer = Answer;
        TurnCount = 1;
        answer_true = false;
        printf("\n\n-----------------------------------------");
        printf("\n| GAME #%d",PlayCount);
        printf("\n-----------------------------------------");
        while( TurnCount < 4 && !answer_true )
        {
            if(TurnCount == 3)
            {
                FinalClue(&Answer);
            }
            printf("\n\nTry %d of 3.",TurnCount);
            printf("\n Your Guess: ");scanf("%d",&Guess);

            if(Guess == Answer)
            {
                if(TurnCount == 1)
                {
                    printf("\nBullseye!");
                }
                printf("\nYour answer is right!");
                answer_true= true;
            }
            else if(Guess > Answer)
            {
                printf("Sorry, your guess is higher than the answer. ");
                TurnCount++;
            }
            else if(Guess < Answer)
            {
                printf("Sorry, your guess is smaller than the answer. ");
                TurnCount++;
            }
        }
        if (TurnCount < 4 && answer_true)
        {
            RoundScore[PlayCount] = ScoreCalc(TurnCount,PlayCount);
            TotalScore += RoundScore[PlayCount];
            printf("\n-----------------------------------");
            printf("\nCongrats, you got %.0f points!",RoundScore[PlayCount]);
            printf("\nYour total score is %.0f",TotalScore);
            Continue = ContinueQuestion(FalseCount);
        }
        else
        {
            RoundScore[PlayCount] = 0;
            printf("\n-----------------------------------");
            printf("\nAww, you got it wrong....");
            printf("\nYour total score is %.0f",TotalScore);
            FalseCount++;
            Continue = ContinueQuestion(FalseCount);
        }
    }while(Continue);
    printf("\n");
    for(i=1;i<=PlayCount;i++)
    {
        printf(" \nGame #%d Score: %.0f",i,RoundScore[i]);
    }
    FinalReport(&FalseCount,&PlayCount,&TotalScore);
    return 0;
}

bool ContinueQuestion(int FalseCount)
{
    //Asks the player, do they want to continue?
    char ContinuePrompt;
        if(FalseCount < 3)
            {
                printf("\nWant to continue?<Y/N>");
                scanf("%s",&ContinuePrompt);
                switch(ContinuePrompt)
                {
                case 'Y':
                    return true;
                    break;
                case 'y':
                    return true;
                    break;
                case 'N':
                    return false;
                    break;
                case 'n':
                    return false;
                    break;
                default:
                    printf("Sorry, you entered wrong command. Program will terminate.");
                    return false;
                }
            }
            else
            {
                printf("\n\nI'm sorry, your game has ended.");
                return false;
            }
}

void FinalClue(int *Answer)
{
    int FinalClueID;
    FinalClueID = rand() % 100 + 1;
    printf("\nFINAL CLUE: ");
    if (FinalClueID%20 == 0)
    {
        printf("Psst, the answer is %d!",*Answer);
    }
    else
    {
        FinalClueID = FinalClueID % 10 + 1;
        if(FinalClueID == 1 || FinalClueID == 3 || FinalClueID == 9)
        {
            if(*Answer % 2 == 0)
            {
                printf("The Answer is an Even number.");
            }
            else
            {
                printf("The Answer is an Odd number.");
            }
        }
        else if(FinalClueID == 2 || FinalClueID == 4 || FinalClueID == 7)
        {
            if(*Answer < 6)
            {
                printf("The Answer is Between 1-5.");
            }
            else
            {
                printf("The Answer is Between 6-10.");
            }
        }
        else if(FinalClueID == 5 || FinalClueID == 8 || FinalClueID == 10)
        {
            if(*Answer == 2 || *Answer == 3 || *Answer == 5 || *Answer == 7)
            {
                printf("The Answer is A Prime Number!");
            }
            else
            {
                printf("The Answer isn't A Prime Number!");
            }
        }
        else
        {
            printf("Whoops, no clue for now!");
        }
    }
}

void FinalReport(int *FalseCount, int *PlayCount, float *FinalScore)
{
    float PlayPercentage;
    //They're declared again because pointers cannot be divided
    int FCount = *FalseCount;
    int PCount = *PlayCount;
    PlayPercentage =((PCount-FCount)*100)/PCount;
    printf("\n\n------------------------------------");
    printf("\nGAME REPORT");
    printf("\n------------------------------------");
    printf("\nYour game has ended.");
    printf("\nYou played %d game(s), with %.2f percent winning percentage.",*PlayCount,PlayPercentage);
    printf("\nYour final score is %.0f",*FinalScore);
    printf("\n---------------------------");
    printf("\n\nTHANK YOU FOR PLAYING!");
    printf("\n-MUHAMMAD RYAN FADHOLI");
}
float ScoreCalc(int TurnCount,int PlayCount)
{
    int TurnScore,PlayScore,BonusScore,Temp;
    float RoundScore;
    BonusScore= rand() % 1000 + 1;
    if(BonusScore % 100 == 0)
    {
        printf("\n\nJACKPOT! You got extra 100000 points!");
        BonusScore = 100000;
    }
    else
    {
        Temp =BonusScore;
        BonusScore = BonusScore % 100;
        BonusScore = Temp - BonusScore + 100;
    }
    TurnScore = (3-TurnCount)*(3-TurnCount)*1000 + 3000;
    PlayScore = PlayCount * 800;
    RoundScore = 3000 + PlayScore + TurnScore + BonusScore;
    return RoundScore;
}
