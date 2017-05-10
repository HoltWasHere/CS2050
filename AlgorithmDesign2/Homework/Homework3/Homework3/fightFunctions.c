#include "game.h"

int fight(Player* playerList, Hero* heroes, Boss* boss)
{
    if(!heroes || !boss || !playerList)
    {
        //No idea how'd I get here, but just in case.
        printf("ERROR: parameters to fightFxns\n");
        freePlayerList(playerList);
        return -1;
    }
    //utility pointer, to move down the list.
    //Just in case we need to get back to the top of the turn order.
    Player* currentActor = playerList;
    //will reference the list of decisions the boss is using for the applicable turns.
    //This will need to be reset once the list of decisions runs out. 
    bossDecision* bossStack = NULL;
    
    while(1)
    {
        //Shows everyone's health on the screen, in a fashion that's pretty. 
        printFightStatus(heroes, boss);
        //The user decides what all the heroes do next. 
        getDecisions(heroes);
        //run through the turn order. Fastest player goes first, all the way to the slowest player. 
        while(currentActor != NULL)
        {
            if(bossStack == NULL)
            {
                //if the boss needs a new set of decisions, that has to be found before
                //anything happens. Otherwise, it will just use what is already there.
                bossStack = getNewListInTree(boss->root, boss->health);
                if(!bossStack)
                {
                    freePlayerList(playerList);
                    printf("ERROR: boss stack is NULL!\n");
                    return -1;
                }
            }
            //If the player is the boss, do his actions.
            if(currentActor->boss != NULL)
            {
                //he'll attack a random hero, I guess.
                Hero* defender = &heroes[rand() % NUMHEROES];
                //make sure the guy he's attacking is alive.
                while(defender->health == 0)
                {
                    defender = &heroes[rand() % NUMHEROES];
                }
                //get next thing from the list of decisions
                boss->nextAction = bossStack->type;
                evaluateDecision(defender, boss, 1);
                //get the next decision prepped. 
                bossStack = bossStack->next;
            }
            //If the player is a hero, just do his action. There's only one boss for now,
            //so that hero will just be attacking him if he's attacking. 
            else
            {
                evaluateDecision(currentActor->hero, boss, 0);
            }
            //remove the player that was just done, and go to the next guy.
            currentActor = currentActor->next;
            free(playerList);
            playerList = currentActor;
        }
        //turn order was exhausted, so a new one has to be made.
        //As of this version, we technically could just use the same list over and over,
        //but if we wanted to have stat modifying actions later, we'd need a whole new list
        //each time. 
        currentActor = createNewPlayerList(heroes, boss);
        if(!currentActor)
        {
            printf("ERROR: turn order list creation failed.\n");
            return -1;
        }
        int check;
        //checks to see if anyone is dead. If they are, they shouldn't be in the list. 
        playerList = resizeListAndCheckBoss(currentActor, &check);
        if(!playerList)
        {
            printf("ERROR: turn order list resizing failed.\n");
            return -1;
        }
        //the check was done above, sees if the boss is dead. If the boss is dead, game's over.
        if(check == 1)
        {
            //as of now, this is the only way to win the fight. 
            freePlayerList(playerList);
            return 0;
        }
        //reset this utility pointer. Just to be consistent. 
        currentActor = playerList;
        //checks to see how many players are left in the turn order once the dead ones 
        //are filtered out. 
        //I have literally no idea why Netbeans complains about this function. Yes, I declared it.
        if(countHeroesInFight(currentActor) < 1)
        {
            //if everyone's dead, game's over.
            freePlayerList(playerList);
            return 1;
        }
    }
    //I should never get here, but just in case...
    printf("ERROR: unexpected code execution\n");
    return -1;
}

Player* resizeListAndCheckBoss(Player* playerList, int* check)
{
    //go through the list similar to what is done in the fight function.
    Player* currentActor = playerList;
    Player* prev = playerList;
    while(currentActor != NULL)
    {
        //if the player is a boss
        if(currentActor->boss != NULL)
        {
            if(currentActor->boss->health <= 0)
            {
                //if the boss is dead, game over. 
                freePlayerList(playerList);
                *check = 1;
                return NULL;
            }
            prev = currentActor;
            currentActor = currentActor->next;
        }
        else
        {
            //check for a dead hero.
            if(currentActor->hero->health <= 0)
            {
                //finds out where the hero is in the list, and repairs the list accordingly.
                if(currentActor == playerList)
                {
                    playerList = playerList->next;
                    free(currentActor);
                    prev = playerList;
                    currentActor = playerList->next;
                }
                else if(currentActor->next == NULL)
                {
                    prev->next = NULL;
                    free(currentActor);
                    break;
                }
                else
                {
                    prev->next = currentActor->next;
                    free(currentActor);
                    currentActor = prev->next;
                }
            }
            else
            {
                //if hero isn't dead, move to next one.
                prev = currentActor;
                currentActor = currentActor->next;
            }
        }
    }
    //return the newly updated list of all players that are alive. 
    return playerList;
}

int countHeroesInFight(Player* list)
{
}

Player* createNewPlayerList(Hero* heroes, Boss* boss)
{
}

void printFightStatus(Hero* heroes, Boss* boss)
{
    int i;
    for(i = 0; i < 3; i++)
    {
        printf("--------%s----------", heroes[i].name);
        if(i == 1)
        {
            printf("\t\t\t\t--------%s----------\n", boss->name);
        }
        else
        {
            printf("\n");
        }
        printf("\t%d/%d", heroes[i].health, heroes[i].maxHealth);
        if(i == 1)
        {
            printf("\t\t\t\t\t%d/%d\n", boss->health, boss->maxHealth);
        }
        else
        {
            printf("\n");
        }
    }
}

void getDecisions(Hero* heroes)
{
    printf("\n\n");
    int i = 0;
    for(i; i < 3; i++)
    {
        if(heroes[i].health > 0)
        {
            printf("Choose your action for %s: \n", heroes[i].name);
            printf("0: Attack\n1: Defend\n2: Heal\n");
            printf(">");
            int choice; 
            scanf("%d", &choice);
            while(0 > choice || choice > 2)
            {
                printf("Invalid choice. Try again: \n");
                printf(">");
                scanf("%d", &choice);
            }
            heroes[i].decision = choice;
        }
    }
}

void evaluateDecision(Hero* hero, Boss* boss, int takingAction)
{
}