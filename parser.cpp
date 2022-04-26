/*
 *
 *  Project P3 - CS4280
 *  Author: Tony Urschler
 *  Date:   04/11/2022
 *
 * */

#include <iostream>
#include <stdio.h>
#include "parser.h"
#include "node.h"
#include "scanner.h"
#include "token.h"

using namespace std;

static string tokenNames[] = {
    "EOF", "Identifier", "Keyword",
    "Operator", "Number"
};
static string keywords[] = {
    "Again", "If", "Assign", "Move", "Show", "Flip", "Name",
    "Home", "Do", "Spot", "Place", "Here", "There"
};
int line = 1;
token_t token;
char nextChar;
FILE* file;

/*
 *  Function:   parser 
 *  Parameters: FILE*
 *  Returns:    node_t*
 *  Desc:       Reads from the file, and determines if the given input
 *              follows the BNF. If it is successful, it returns a root
 *              node for the parse tree.
 * */
node_t* parser(FILE *inputFile) {
    node_t* root;
    file = inputFile;

    // start checking BNF by calling S()
    root = S();

    // check the next token is EOF
    nextChar = removeWhiteSpace(file);
    token = scanner(file, nextChar, line);
    if (token.tokenID == EOFTkn)
        return root;
    else {
        printf("ERROR: Line %d: Expected EOF Token\n", token.lineNumber);
        exit(EXIT_FAILURE);
    }
}

/*
 *  Function:   S 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "S" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* S() {
    node_t* nodePtr = new node_t("S", token_t());
    
    nextChar = removeWhiteSpace(file);
    token = scanner(file, nextChar, line);
    
    // check if "Name"
    if (token.tokenInstance == "Name") {
        nodePtr->child1 = new node_t("", token);
        
        // check if Identifier
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenID != IDTkn) {
            printf("ERROR S(): Line %d: Expected IDTkn got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        }
        nodePtr->child2 = new node_t("", token);
        
        // check if "Spot"
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenInstance != "Spot") {
            printf("ERROR S(): Line %d: Expected \"Spot\" got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        }
        nodePtr->child3 = new node_t("", token);
        
        // check if Identifier
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenID != IDTkn) {
            printf("ERROR S(): Line %d: Expected IDTkn got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        }
        nodePtr->child4 = new node_t("", token);

        // check <R>
        nodePtr->child5 = R();
        
        // check if "Show"
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenInstance != "Show") {
            printf("ERROR S(): Line %d: Expected \"Show\" got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        }
        
        // check if <E> good
        nodePtr->child6 = E();

        return nodePtr;
    }
    else {
        printf("ERROR S(): Line %d: Expected \"Name\" got %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    }
}

/*
 *  Function:   R 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "R" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* R() {
    node_t* nodePtr = new node_t("R", token_t());

    // check if "Place"
    nextChar = removeWhiteSpace(file);
    token = scanner(file, nextChar, line);
    if (token.tokenInstance == "Place") {
        nodePtr->child1 = new node_t("", token);
        
        // ensure <A> correct
        nodePtr->child2 = A();

        // ensure <B> correct
        nodePtr->child3 = B();

        // check if "Home"
        if (token.tokenInstance != "Home") {
            printf("ERROR R(): Line %d: Expected \"Home\" got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        }
        nodePtr->child4 = new node_t("", token);
        
        return nodePtr;
    }    
    else {
        printf("ERROR R(): Line %d: Expected \"Place\" got %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    }
}

/*
 *  Function:   E 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "E" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* E() {
    node_t* nodePtr = new node_t("E", token_t());
    
    // store given token
    nodePtr->child1 = new node_t("", token);
    
    // check if Identifier
    nextChar = removeWhiteSpace(file);
    token = scanner(file, nextChar, line);
    if (token.tokenID != IDTkn) {
        printf("ERROR E(): Line %d: Expected ID Token got %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    } 
    nodePtr->child2 = new node_t("", token);

    return nodePtr;
}

/*
 *  Function:   A 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "A" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* A() {
    node_t* nodePtr = new node_t("A", token_t());

    // check if "Name"
    nextChar = removeWhiteSpace(file);
    token = scanner(file, nextChar, line);
    if (token.tokenInstance == "Name") {
        nodePtr->child1 = new node_t("", token);
        
        // check if Identifier
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenID != IDTkn) {
            printf("ERROR A(): Line %d: Expected ID Token got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        } 
        nodePtr->child2 = new node_t("", token);

        return nodePtr;
    }
    else {
        printf("ERROR A(): Line %d: Expected \"Name\" got %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    }
}

/*
 *  Function:   B 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "B" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* B() {
    node_t* nodePtr = new node_t("B", token_t());

    // check if "."
    nextChar = removeWhiteSpace(file);
    token = scanner(file, nextChar, line);
    if (token.tokenInstance == ".") {
        nodePtr->child1 = new node_t("", token);

        // check if <C> good
        nodePtr->child2 = C();
        
        // check if "."
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenInstance != ".") {
            printf("ERROR B(): Line %d: Expected \".\" got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        } 
        nodePtr->child3 = new node_t("", token);

        // check if <B> good
        nodePtr->child4 = B();
        
        return nodePtr;
    }
    // check if follows <D>
    else if (token.tokenInstance == "/" ||
             token.tokenInstance == "Assign" ||
             token.tokenInstance == "Spot" ||
             token.tokenInstance == "Move" ||
             token.tokenInstance == "Flip" ||
             token.tokenInstance == "Show" ||
             token.tokenInstance == "{") {
        nodePtr->child1 = D();

        // check if <B> good
        nodePtr->child2 = B();
        
        return nodePtr;
    }
    // indicate <B> empty
    else {
        nodePtr->child1 = new node_t("Empty", token_t());
        return nodePtr;
    }
}

/*
 *  Function:   C 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "C" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* C() {
    node_t* nodePtr = new node_t("C", token_t());
    
    // get first char and token
    nextChar = removeWhiteSpace(file);
    token = scanner(file, nextChar, line);
    
    // see if it uses <F>
    if (token.tokenInstance == "{")
        nodePtr->child1 = F();
    // see if it uses <G>
    else if (token.tokenInstance == "Here")
        nodePtr->child1 = G();
    else {
        printf("ERROR C(): Line %d: Expected \"{\" got %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    }
    return nodePtr;
}

/*
 *  Function:   D 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "D" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* D() {
    node_t* nodePtr = new node_t("D", token_t());

    if (token.tokenInstance == "/") {
        nodePtr->child1 = H();
    }
    else if (token.tokenInstance == "Assign") {
        nodePtr->child1 = J();
    }
    else if (token.tokenInstance == "Spot" ||
             token.tokenInstance == "Move") {
        nodePtr->child1 = K();
    }
    else if (token.tokenInstance == "Flip") {
        nodePtr->child1 = L();
    }
    else if (token.tokenInstance == "Show") {
        nodePtr->child1 = E();
    }
    else if (token.tokenInstance == "{") {
        nodePtr->child1 = F();
    }
    else {
        printf("ERROR D(): Line %d: Invalid token %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    }
    return nodePtr;
}

/*
 *  Function:   F 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "F" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* F() {
    node_t* nodePtr = new node_t("F", token_t());

    // store given token
    nodePtr->child1 = new node_t("", token);
    
    nextChar = removeWhiteSpace(file);
    token = scanner(file, nextChar, line);

    // check if follows the "If" rule
    if (token.tokenInstance == "If") {
        nodePtr->child2 = new node_t("", token);

        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenID != IDTkn) {
            printf("ERROR F(): Line %d: Expected ID Token got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        } 
        nodePtr->child3 = new node_t("", token);
        
        // check <T> and <W>
        nodePtr->child4 = T();
        nodePtr->child5 = W();

        // check <D>
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenInstance != "/" &&
             token.tokenInstance != "Assign" &&
             token.tokenInstance != "Spot" &&
             token.tokenInstance != "Move" &&
             token.tokenInstance != "Flip" &&
             token.tokenInstance != "Show" &&
             token.tokenInstance != "{") {
            printf("ERROR F(): Line %d: Invalid First <D> token got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        }
        nodePtr->child6 = D();
        
        // check if "}"
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenInstance != "}") {
            printf("ERROR F(): Line %d: Expected \"}\" got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        } 
        nodePtr->child7 = new node_t("", token);
    } 
    // check if follows the "Do" rule
    else if (token.tokenInstance == "Do") {
        nodePtr->child2 = new node_t("", token);

        // check if "Again"
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenInstance != "Again") {
            printf("ERROR F(): Line %d: Expected \"Again\" got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        } 
        nodePtr->child3 = new node_t("", token);
        
        // check if follows <D>
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenInstance != "/" &&
             token.tokenInstance != "Assign" &&
             token.tokenInstance != "Spot" &&
             token.tokenInstance != "Move" &&
             token.tokenInstance != "Flip" &&
             token.tokenInstance != "Show" &&
             token.tokenInstance != "{") {
            printf("ERROR F(): Line %d: Invalid First<D> %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        }
        nodePtr->child4 = D();
       
        // check <T> and <W>
        nodePtr->child5 = T();
        nodePtr->child6 = W();

        // check if "}"
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenInstance != "}") {
            printf("ERROR F(): Line %d: Expected \"}\" got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        } 
        nodePtr->child7 = new node_t("", token);
    }
    // else it's an error
    else {
        printf("ERROR F(): Line %d: Expected \"If\" or \"Do\" got %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    }

    return nodePtr;
}

/*
 *  Function:   G 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "G" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* G() {
    node_t* nodePtr = new node_t("G", token_t());
    nodePtr->child1 = new node_t("", token);
    
    // check if Number
    nextChar = removeWhiteSpace(file);
    token = scanner(file, nextChar, line);
    if (token.tokenID != NumTkn) {
        printf("ERROR G(): Line %d: Expected Number Token got %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    } 
    nodePtr->child2 = new node_t("", token);

    // check if "There"
    nextChar = removeWhiteSpace(file);
    token = scanner(file, nextChar, line);
    if (token.tokenInstance != "There") {
        printf("ERROR G(): Line %d: Expected \"There\" got %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    } 
    nodePtr->child3 = new node_t("", token);

    return nodePtr;
}

/*
 *  Function:   T 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "T" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* T() {
    node_t* nodePtr = new node_t("T", token_t());

    nextChar = removeWhiteSpace(file);
    token = scanner(file, nextChar, line);

    // check if "<<" or "<-"
    if (token.tokenInstance == "<<" ||
        token.tokenInstance == "<-") {
        nodePtr->child1 = new node_t("", token);
        return nodePtr;
    }
    else {
        printf("ERROR T(): Line %d: Expected \"<<\" or \"<-\" got %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    }
}

/*
 *  Function:   V 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "V" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* V() {
    node_t* nodePtr = new node_t("V", token_t());

    // check if +, %, or &
    if (token.tokenInstance == "+" ||
        token.tokenInstance == "%" ||
        token.tokenInstance == "&") {
        nodePtr->child1 = new node_t("", token);
        return nodePtr;
    }
    else {
        printf("ERROR V(): Line %d: Expected + or %% or & got %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    }
}

/*
 *  Function:   H 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "H" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* H() {
    node_t* nodePtr = new node_t("H", token_t());
    nodePtr->child1 = new node_t("", token);
    
    // checking <Z>
    nodePtr->child2 = Z();

    return nodePtr;
}

/*
 *  Function:   J 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "J" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* J() {
    node_t* nodePtr = new node_t("J", token_t());
    nodePtr->child1 = new node_t("", token);
    
    // checking if Identifier
    nextChar = removeWhiteSpace(file);
    token = scanner(file, nextChar, line);
    if (token.tokenID != IDTkn) {
        printf("ERROR J(): Line %d: Expected ID Token got %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    } 
    nodePtr->child2 = new node_t("", token);
    
    // checking <D>
    nextChar = removeWhiteSpace(file);
    token = scanner(file, nextChar, line);
    if (token.tokenInstance != "/" &&
         token.tokenInstance != "Assign" &&
         token.tokenInstance != "Spot" &&
         token.tokenInstance != "Move" &&
         token.tokenInstance != "Flip" &&
         token.tokenInstance != "Show" &&
         token.tokenInstance != "{") {
        printf("ERROR J(): Line %d: Invalid First <D> Token got %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    }
    nodePtr->child3 = D();

    return nodePtr;
}

/*
 *  Function:   K 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "K" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* K() {
    node_t* nodePtr = new node_t("K", token_t());
    
    // check if "Spot"
    if (token.tokenInstance == "Spot") {
        nodePtr->child1 = new node_t("", token);
        
        // check if Number
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenID != NumTkn) {
            printf("ERROR K(): Line %d: Expected Number Token got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        } 
        nodePtr->child2 = new node_t("", token);

        // check if "Show"
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenInstance != "Show") {
            printf("ERROR K(): Line %d: Expected \"Show\" got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        } 
        nodePtr->child3 = new node_t("", token);
    
        // check if Number
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenID != NumTkn) {
            printf("ERROR K(): Line %d: Expected Number Token got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        } 
        nodePtr->child4 = new node_t("", token);
    }
    // check if "Move"
    else if (token.tokenInstance == "Move") {
        nodePtr->child1 = new node_t("", token);
        
        // check if Identifier
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenID != IDTkn) {
            printf("ERROR K(): Line %d: Expected ID Token got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        } 
        nodePtr->child2 = new node_t("", token);

        // check if "Show"
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenInstance != "Show") {
            printf("ERROR K(): Line %d: Expected \"Show\" got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        } 
        nodePtr->child3 = new node_t("", token);
        
        // check if Identifier
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenID != IDTkn) {
            printf("ERROR K(): Line %d: Expected ID Token got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        } 
        nodePtr->child4 = new node_t("", token);
    }
    else {
        printf("ERROR K(): Line %d: Expected \"Spot\" or \"Move\" got %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    }

    return nodePtr;
}

/*
 *  Function:   L 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "L" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* L() {
    node_t* nodePtr = new node_t("L", token_t());
    nodePtr->child1 = new node_t("", token);
    
    // check if Identifier
    nextChar = removeWhiteSpace(file);
    token = scanner(file, nextChar, line);
    if (token.tokenID != IDTkn) {
        printf("ERROR L(): Line %d: Expected ID Token got %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    } 
    nodePtr->child2 = new node_t("", token);

    return nodePtr;
}

/*
 *  Function:   W 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "W" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* W() {
    node_t* nodePtr = new node_t("W", token_t());
    
    // get first char and token
    nextChar = removeWhiteSpace(file);
    token = scanner(file, nextChar, line);

    // check if Identifier
    if (token.tokenID == NumTkn) {
        nodePtr->child1 = new node_t("", token);
        
        // check <V>
        nextChar = removeWhiteSpace(file);
        token = scanner(file, nextChar, line);
        if (token.tokenInstance == "+" ||
            token.tokenInstance == "%" ||
            token.tokenInstance == "&") {
            nodePtr->child2 = new node_t("", token);
            nodePtr->child3 = V();
            
            // check if Number
            nextChar = removeWhiteSpace(file);
            token = scanner(file, nextChar, line);
            if (token.tokenID != NumTkn) {
                printf("ERROR W(): Line %d: Expected Number Token got %s\n",
                    token.lineNumber, token.tokenInstance.c_str());
                exit(EXIT_FAILURE);
            }
            nodePtr->child4 = new node_t("", token);
        }
        // check if "."
        else if (token.tokenInstance == ".")
            nodePtr->child2 = new node_t("", token);
        else {
            printf("ERROR W(): Line %d: Expected got %s\n",
                token.lineNumber, token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        }
    }
    else {
        printf("ERROR W(): Line %d: Expected Number Token got %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    }
    return nodePtr;
}

/*
 *  Function:   Z 
 *  Parameters: None
 *  Returns:    node_t*
 *  Desc:       Determines if the given input follows the "Z" rule. Returns
 *              a pointer to a node if it does, else ends in error.
 * */
node_t* Z() {
    node_t* nodePtr = new node_t("Z", token_t());
    
    // check if Identifier or Number
    nextChar = removeWhiteSpace(file);
    token = scanner(file, nextChar, line);
    if (token.tokenID == IDTkn || token.tokenID == NumTkn) {
        nodePtr->child1 = new node_t("", token);
        return nodePtr;
    }
    else {
        printf("ERROR Z(): Line %d: Expected Number or ID Token got %s\n",
            token.lineNumber, token.tokenInstance.c_str());
        exit(EXIT_FAILURE);
    }
}


/*
 *  Function:   keywordValid
 *  Parameters: string
 *  Returns:    bool
 *  Desc:       Determines if a keyword is in the keywords array. If it
 *              is, it returns true. Else false.
 * */
bool keywordValid(string keyword) {
    // loop until a keyword matches
    for (int i = 0; i < 13; i++) {
        if (keyword == keywords[i])
            return true;
    }
    return false;
}

/*
 *  Function:   removeWhiteSpace 
 *  Parameters: FILE*
 *  Returns:    char
 *  Desc:       Removes any whitespace and comments from until the next token.
 *              It returns a lookahead, or the next char in the file.
 * */
char removeWhiteSpace(FILE *file) {
    char nextChar = fgetc(file);

    // skip over comments
    if (nextChar == '*') {
        nextChar = fgetc(file);
        while (nextChar != '*' && nextChar != EOF) {
            nextChar = fgetc(file);
        }
        nextChar = fgetc(file);
    }
    
    // skip over white space
    else if (isspace(nextChar)) {
        if (nextChar == '\n')
            line++;
        nextChar = fgetc(file);
        while (isspace(nextChar) && nextChar != EOF) {
            nextChar = fgetc(file);
        }
    }
    return nextChar;
}
