#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // if name matches a candidate update preferences accordingly pref[i][j]
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        int j = 0;
        // increment through [j] (candidate) until a candidate who is not eliminated is found
        if (candidates[preferences[i][j]].eliminated)
        {
            do
            {
                j++;
            }
            while (candidates[preferences[i][j]].eliminated);
        }
        // update their votes accordingly
        candidates[preferences[i][j]].votes++;
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // calculate majority AND highest votes
    int majority = (voter_count / 2) + 1;
    int highest_votes = candidates[0].votes;
    int index = 0;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // find the candidate with the highest votes - store their index AND vote total
        if (candidates[i + 1].votes > highest_votes)
        {
            highest_votes = candidates[i + 1].votes;
            index = i + 1;
        }
        // if there is a tie - return false
        else if (candidates[i].votes == candidates[i + 1].votes)
        {
            return false;
        }
    }
    // print the winner if there is no tie
    if (candidates[index].votes >= majority)
    {
        printf("%s\n", candidates[index].name);
        return true;
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // start the min process with the first candidates vote total
    int min = candidates[0].votes;
    for (int i = 0; i < candidate_count; i++)
    {
        // if not eliminated AND vote total is lower than previous candidate - update min
        if (!candidates[i].eliminated)
        {
            if (min > candidates[i].votes)
            {
                min = candidates[i].votes;
            }
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int remaining_candidates = 0;
    int count = 0;
    // for loop to calculate the remaining candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            remaining_candidates++;
        }
    }
    // for loop to determine if there is a tie
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            if (candidates[i].votes == min)
            {
                count ++;
            }
        }
        // if all candidates tied return true
        if (count == remaining_candidates)
        {
            return true;
        }
    }
    // else
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate is not eliminated and has the lowest amount of votes
        // eliminate them!
        if ((!candidates[i].eliminated) && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
