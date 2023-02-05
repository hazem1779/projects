#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
            i=i-1;
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
int k=0;
bool vote(string name)
{

          if (strcmp(candidates[k].name,name)==0 )
            {
            candidates[k].votes++;
            k=0;
            return true ;
            }
            else if (k<candidate_count)
            {
            k++ ;
            return vote(name) ;
            }
    k=0;

    return false;


}
int m=0 ;
//int hhh=0 ;
//string winner[9];
string winner1 ;
// Print the winner (or winners) of the election
void print_winner(void)
{

    // TODO
    for(int K=0 ; K <candidate_count;K++)
    {
    
        if(candidates[K].votes > m)
        {
         m=candidates[K].votes;    
        }
        //if(m==candidates[K].votes)
        //{
          //winner1 = candidates[K].name ;
        //}
    }
    for(int K=0 ; K <candidate_count;K++)
    {
        if (m==candidates[K].votes)
        {
            winner1 = candidates[K].name ;
            printf("%s\n",winner1);
        }
    }
 
  return ;
}
