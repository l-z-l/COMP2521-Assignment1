
// creating a macro
#define abs(a) ((a) < 0 ? -(a) : (a))


int isHeight(BSTree t) {
    if (t == NULL) {
        return 0;
    } 

}



int printHeightDiff(BSTree t) {
    if (t == NULL) {
        return 0;
    }
    int lHeight = printHeightDiff(t->left);
    int rHeight = printHeightDiff(t->right);
    int diff = abs(lHeight - rHeight);
    if (lHeight == NOT_balanced || rHeight == NOT_balanced || abs(lHeight - rHeight) > 1) {

    }


}


int 