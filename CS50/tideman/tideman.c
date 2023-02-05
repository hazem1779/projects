#include <cs50.h>
#include <stdio.h>
#include <string.h>
// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                j=j-1;
            }
        }

        record_preferences(ranks);
        printf("\n");

    }

    add_pairs();
    //printf("pair count%i\n",pair_count);
    //printf("pref %i %i \n",preferences[2][1],preferences[1][2]);
    //printf("%i\n%i\n%i\n%i\n%i\n%i\n",pairs[0].winner,pairs[0].loser,pairs[1].winner,pairs[1].loser,pairs[2].winner,pairs[2].loser);
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;

}

// Update ranks given a new vote
int k=0;
bool vote(int rank, string name, int ranks[])
{
    if (strcmp(candidates[k],name)==0)
    {
       ranks[rank]=k;
        k=0;
        return true ;
    }
    else if (k<candidate_count-1)
    {
        k++ ;
        return vote(rank,name,ranks);

    }
    else
    {
    k=0;
    return false ;
    }

}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    for (int i=0 ; i < candidate_count; i++)
    {
       for (int j=0 ; j < candidate_count; j++)
       {
          if(i < j)
          {
           preferences[ranks[i]][ranks[j]]++ ;
          }
       }
    }
    return;
}
int ff = -1;
// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

    // TODO
    for (int i=0 ; i < candidate_count-1; i++)
    {
        for (int j=0 ; j < candidate_count-1; j++)
        {

            if(i<=j)
            {
                ff++ ;
                if(preferences[i][j+1]>preferences[j+1][i])
                {
                pairs[ff].winner= i ;
                pairs[ff].loser= j+1  ;
                }
                else if (preferences[i][j+1]<preferences[j+1][i])
                {
                pairs[ff].winner= j+1 ;
                pairs[ff].loser= i ;
                }
                else if (preferences[i][j+1]==preferences[j+1][i])
                {
                ff--;
                }
            }
        }
    }
    pair_count=ff+1;
    return;
}

// Sort pairs in decreasing order by strength of victory
int w =0 ;
int l =0 ;
void sort_pairs(void)
{

    for (int z=0 ; z < pair_count-1; z++)
    {
        for(int j=0 ; j < pair_count-1; j++)
        {
     if(preferences[pairs[z].winner][pairs[z].loser] < preferences[pairs[j+1].winner][pairs[j+1].loser])
            {
                w=pairs[z].winner ;
                l=pairs[z].loser ;
                pairs[z].winner= pairs[j+1].winner ;
                pairs[z].loser=pairs[j+1].loser ;
                pairs[j+1].winner= w ;
                pairs[j+1].loser= l ;
            }
        }
    }
   // printf("%i\n%i\n%i\n%i\n%i\n%i\n",pairs[0].winner,pairs[0].loser,pairs[1].winner,pairs[1].loser,pairs[2].winner,pairs[2].loser);

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
int array[MAX];
int counter ;
void lock_pairs(void)
{
    // editing the locked graph
    for (int i=0 ; i < pair_count; i++)
    {
     locked[pairs[i].winner][pairs[i].loser]=true ;
    }
   // if(كل صف فيه ترو واحدة الغي اخر لوك خليه فولس)
   for(int I=0 ; I < pair_count; I++)
    {
      counter=0;
      for(int J=0 ; J < pair_count; J++)
      {
        if(locked[I][J] == true )
        {
            counter++ ;
            
        }
        array[I]=counter ;
      }
    } 
    int hhh=0 ;   
    for(int A=0 ; A < pair_count; A++)
    {
        if(array[A]==1)
       {
            hhh++ ;
        }
    } 
    if(hhh == pair_count)
    {
        locked[pairs[pair_count-1].winner][pairs[pair_count-1].loser]=false ;
    }
    
    return;
}

// Print the winner of the election
int Array[MAX];
int C ;
void print_winner(void)
{
     for(int I=0 ; I < candidate_count; I++)
    {
      C=0 ;
      for(int J=0 ; J < candidate_count; J++)
      {
        if(locked[J][I]==false)
        {
            C++ ;
        }
      }
      if (C==candidate_count)
      {
        printf("%s\n",candidates[I]);
      }
      
    }
    return;
}

