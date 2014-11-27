#include <cstdlib>
#include <iomanip>

#define MAX_KEY 999999
#define MIN_KEY 100000

using namespace std;

// Generate a 6 digit key in the range 100000 to 999999

class RandomKey
{
public:
    RandomKey (long seed);
    void Seed (long seed);
    void Seed ();
    long GenerateNextRandomKey ();
private:
    long nextSeed;
    long randomNo;
};

RandomKey::RandomKey (long seed)
{
    nextSeed = seed;
}

void RandomKey::Seed (long seed)
{
    nextSeed = seed;
}

void RandomKey::Seed ()
{
    srand (nextSeed);
}

long RandomKey::GenerateNextRandomKey ()
{
    randomNo = ((double) rand () / RAND_MAX) * (MAX_KEY - MIN_KEY + 1) + MIN_KEY;
    nextSeed = randomNo;
    return randomNo;
}

// Generate a random number in the range 1 to RAND_MAX

class RandomNo
{
public:
    RandomNo (long seed);
    void Seed (long seed);
    void Seed ();
    long GenerateNextRandomNo ();
private:
    long nextSeed;
    long randomNo;
};

RandomNo::RandomNo (long seed)
{
    nextSeed = seed;
}

void RandomNo::Seed (long seed)
{
    nextSeed = seed;
}

void RandomNo::Seed ()
{
    srand (nextSeed);
}

long RandomNo::GenerateNextRandomNo ()
{
    randomNo = rand () % (RAND_MAX - 1) + 1;
    nextSeed = randomNo;
    return randomNo;
}

