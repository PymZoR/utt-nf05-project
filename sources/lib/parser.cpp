#include "parser.h"



Parser::Parser(QString source)
{
    this->source = source;
    this->lexer = new Lexer(source);
}


Parser::~Parser() {}


Calculable* Parser::run()
{
    QList<Token> tokens = this->lexer->run();

    if (tokens.length() == 0)
    {
        return NULL;
    }

    int assignationNumber = 0;

    foreach (Token token, tokens)
    {
        if (token.getKind() == T_ASSIGNMENT)
        {
            assignationNumber++;
        }
    }

    if (assignationNumber > 1)
    {
        throw std::runtime_error("Multiple assignation");
        return NULL;
    }
    else
    {
        Node *tree = this->generateTree(tokens);

        if (tree == NULL)
            return NULL;

        return tree->execute();
    }
}


Node* Parser::generateTree(QList<Token> tokens)
{
    if (tokens.length() == 1)
    {
        Token token = tokens[0];
        TokenKind kind = token.getKind();


        if (kind == T_SCALAR || kind == T_MATRIX || kind == T_STRING)
        {
            ExpressionNode* node = new ExpressionNode(tokens);
            return node;
        }
        else
        {
            throw std::runtime_error("Operator alone");
            return NULL;
        }
    }
    else
    {
        int assignementPos = 0;

        for (int i = 0; i < tokens.length(); i++)
        {
            //Search for an assignement
            if (!assignementPos && tokens[i].getKind() == T_ASSIGNMENT)
            {
                //found
                assignementPos = i;
                break;
            }
        }

        if (!assignementPos)
        {
            return new ExpressionNode(tokens);
        }
        else
        {
            //Create assignation node. structure : "varName := expression"
            //
            QList<Token> varName = tokens.mid(0, assignementPos);

            if (varName.length() > 1 || varName[0].getKind() != T_STRING || (assignementPos >= tokens.length()-1))
            {
                throw std::runtime_error("Invalid syntax for assignment");
                return NULL;
            }

            ExpressionNode* right = (ExpressionNode*) generateTree(tokens.mid(assignementPos+1, tokens.length()-1));
            VarNode *varNode = VarNode::getVar(varName[0].getValue());


            AssignationNode *assignationNode = new AssignationNode(varNode, right);
            return assignationNode;
        }
    }
}


bool Parser::isFunction(Token token)
{
    QString value = token.getValue().toLower();

    return (value == "cof"
            || value == "det"
            || value == "trans"
            || value == "co"
            || value == "i"
            || value == "inv"
            || value == "trace"
            || value == "norm"
            || value == "solve");
}
