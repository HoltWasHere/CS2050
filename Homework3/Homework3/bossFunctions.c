#include "game.h" 

bossDecision* addDecisionNodeToList(bossDecision* top, bossDecision* newTop)
{
    newTop->next = top;//make current top the next one down
    return newTop;//Return new top to assign it to top pointer
    
}
bossDecisionNode* addNodeToDecisionTree(bossDecisionNode* root, bossDecisionNode* newNode)
{
/*
    if(!root)//New tree and assign current
    {
        return newNode;
    }

    else if(newNode->healthMin < root->healthMin)
    {
        root->leftNode = addNodeToDecisionTree(root->leftNode, newNode);
    }
    else if(newNode->healthMax> root->healthMax)
    {
        root->rightNode = addNodeToDecisionTree(root->rightNode, newNode);
    }
*/

    
    return root;
}

bossDecision* getNewListInTree(bossDecisionNode* root, int currentBossHealth)
{
    return NULL;
}